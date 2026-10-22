"""运行当前作答；按文件类型与所在系统选择既有构建工具。运行不等于判题。"""
import argparse
import json
import subprocess
import sys
from pathlib import Path
from multifile import student_entry

ROOT = Path(__file__).resolve().parents[1]


def source_path(name):
    p = Path(name).resolve()
    if not p.is_relative_to(ROOT) or not p.is_file():
        raise ValueError('请选择学习区内自己的作答文件。')
    if p.name == 'README.md':
        cards = json.loads((ROOT / 'tools/answer-cards.json').read_text(encoding='utf-8'))
        hits = [c for c in cards if (ROOT / c['guide']).resolve() == p]
        if len(hits) != 1:
            raise ValueError('这是章节或多题目录。请先打开具体题目的作答文件，再运行。')
        p = (ROOT / hits[0]['work']).resolve()
    if p.name.startswith(('reference', '参考')) or '参考实现' in p.parts:
        raise ValueError('当前是参考实现，请先打开自己的作答文件。')
    return student_entry(ROOT, p)


def plan(name, sample=False):
    p = source_path(name)
    if p.suffix not in ('.cpp', '.c', '.sh'):
        raise ValueError('本入口运行C/C++或Shell作答。数学文字题在作答文档中填写并人工核对。')
    shell = p.suffix == '.sh'
    tool = 'wsl-study.py' if sys.platform == 'linux' else 'study.py'
    args = [sys.executable, str(ROOT / 'tools' / tool), 'shell' if shell else 'run', str(p)]
    cards = json.loads((ROOT / 'tools/answer-cards.json').read_text(encoding='utf-8'))
    if any(c['check'] == 'svg' and (ROOT / c['work']).resolve() == p for c in cards):
        args = [sys.executable, str(ROOT / 'tools/render-ch02.py'), str(p)]
    if sample:
        if shell:
            raise ValueError('Shell练习请按本题要求传参，不使用C++的input.txt入口。')
        inp = p.parent / 'input.txt'
        if not inp.is_file():
            raise ValueError('这道题没有input.txt。请选“本题：编译运行”，按题目输入数据。')
        args += ['--input', str(inp)]
    return p, args


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('file')
    parser.add_argument('--input', action='store_true', dest='sample')
    parser.add_argument('--只看命令', action='store_true', dest='explain')
    a = parser.parse_args()
    try:
        p, args = plan(a.file, a.sample)
    except ValueError as e:
        print(e, file=sys.stderr)
        return 2
    print('运行自己的作答：' + str(p.relative_to(ROOT)), flush=True)
    print('这一步只运行程序；检查题目请另选“本题：检查作答”。', flush=True)
    if a.explain:
        print(json.dumps(args, ensure_ascii=False))
        return 0
    return subprocess.run(args, cwd=ROOT).returncode


if __name__ == '__main__':
    raise SystemExit(main())
