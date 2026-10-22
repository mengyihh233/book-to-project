"""检查并应用更新，保证你自己的作答不被覆盖。

用法：
    python tools/update.py            # 只看有没有新版本
    python tools/update.py --apply    # 备份改动 -> 拉取 -> 把你的作答放回去

安全约定：
- 只处理 git 仓库；不是 git 仓库时提示改用压缩包。
- 应用更新前，把你改过的文件整份复制到 我的备份/<时间>/。
- 拉取后再把备份复制回来，所以**你的作答永远以你的版本为准**。
- 如果某个文件上游也改过，会单独列出来，并保留一份 上游版本.<扩展名> 供对照。
"""
import argparse
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BACKUP_DIR = ROOT / '我的备份'
# 这些文件不参与“恢复”，避免把备份目录自己套进去
SKIP_RESTORE = {'tools/update.py', 'VERSION', 'CHANGELOG.md', 'README.md',
                'LICENSE', '.gitignore'}


def git(*args, check=True, capture=True):
    result = subprocess.run(['git', *args], cwd=str(ROOT), capture_output=capture,
                            text=True, encoding='utf-8', errors='replace')
    if check and result.returncode != 0:
        raise RuntimeError((result.stderr or result.stdout or '').strip() or 'git 命令失败')
    return result


def is_repo():
    try:
        git('rev-parse', '--is-inside-work-tree')
        return True
    except Exception:
        return False


def changed_files():
    out = git('status', '--porcelain').stdout
    files = []
    for line in out.split('\n'):
        if not line.strip():
            continue
        status, path = line[:2], line[3:].strip()
        if status.strip() == '??':
            continue  # 未跟踪的新文件不参与恢复，也不会被拉取覆盖
        if ' -> ' in path:  # 重命名
            path = path.split(' -> ')[-1]
        files.append(path.strip('"'))
    return files


def upstream_changes():
    git('fetch', '--quiet', 'origin', check=False)
    branch = git('rev-parse', '--abbrev-ref', 'HEAD').stdout.strip() or 'main'
    behind = git('rev-list', '--count', 'HEAD..origin/' + branch, check=False).stdout.strip()
    local = git('rev-list', '--count', 'origin/' + branch + '..HEAD', check=False).stdout.strip()
    files = git('diff', '--name-only', 'HEAD..origin/' + branch, check=False).stdout.split('\n')
    return branch, int(behind or 0), int(local or 0), [f for f in files if f.strip()]


def main():
    parser = argparse.ArgumentParser(description='检查并应用更新')
    parser.add_argument('--apply', action='store_true', help='真的执行更新')
    args = parser.parse_args()

    if not is_repo():
        print('这个目录不是 git 仓库，没法自动更新。')
        print('请到项目主页下载最新压缩包，解压后把自己的作答文件复制过去。')
        return 1

    branch, behind, local, files = upstream_changes()
    print('当前分支：%s' % branch)
    if behind == 0:
        print('已经是最新版本，没有需要更新的内容。')
        return 0
    print('有 %d 个提交可以更新，涉及 %d 个文件。' % (behind, len(files)))
    for name in files[:12]:
        print('  -', name)
    if len(files) > 12:
        print('  …… 还有 %d 个' % (len(files) - 12))
    if local:
        print('注意：你本地有 %d 个提交不在上游，更新会保留它们。' % local)

    mine = changed_files()
    if mine:
        print('\n你自己改过 %d 个文件，更新前会先备份：' % len(mine))
        for name in mine[:12]:
            print('  -', name)
        if len(mine) > 12:
            print('  …… 还有 %d 个' % (len(mine) - 12))

    if not args.apply:
        print('\n这只是检查。确认要更新就运行：python tools/update.py --apply')
        return 0

    stamp = time.strftime('%Y%m%d-%H%M%S')
    backup = BACKUP_DIR / stamp
    for name in mine:
        src = ROOT / name
        if src.is_file():
            dst = backup / name
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
    if mine:
        print('\n已备份到：%s' % backup)

    # 先记下上游要改哪些文件，恢复时能判断“两边都改过”
    touched = set(files)
    git('checkout', '--', '.')
    pull = git('pull', '--ff-only', check=False)
    if pull.returncode != 0:
        print('拉取失败：')
        print((pull.stderr or pull.stdout).strip()[:600])
        print('你的备份还在 %s，可以用它恢复。' % backup)
        return 1

    conflicts = []
    for name in mine:
        if name in SKIP_RESTORE:
            continue
        src = backup / name
        dst = ROOT / name
        if not src.is_file() or not dst.parent.is_dir():
            continue
        if name in touched:
            keep = dst.with_name(dst.name + '.上游版本')
            shutil.copy2(dst, keep)
            conflicts.append(name)
        shutil.copy2(src, dst)

    print('\n更新完成。')
    if mine:
        print('已把你的 %d 个文件放回原位。' % len([n for n in mine if n not in SKIP_RESTORE]))
    if conflicts:
        print('下面这些文件上游也改过，已保留你的版本，另存了一份新的：')
        for name in conflicts[:12]:
            print('  - %s（新版：%s.上游版本）' % (name, Path(name).name))
    print('备份目录可以自己清理，它不会被提交：%s' % BACKUP_DIR)
    return 0


if __name__ == '__main__':
    sys.exit(main())
