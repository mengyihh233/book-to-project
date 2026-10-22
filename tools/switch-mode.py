"""在「引导版」和「从零写」之间切换，判分入口始终是同一个 work.cpp。

- 引导版：main 与辅助函数已给出，只补函数体（现在大部分题的样子）。
- 从零写：只留题头和一个空行，include、函数、main 全由自己写。

切换时会把当前版本存到 模板/<相对路径>，所以随时可以切回来，不会丢东西。
"""
import argparse
import json
import re
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TEMPLATE_DIR = ROOT / '模板'
MODES = ROOT / 'tools/exercise-modes.json'
MARK = '// 【本题说明结束】'

# 默认从零写的题：章内综合练习、第4章整段式的 1–4 题、每章最后一题。
# 理由见 README「两种模式」：整合性的题不该再给骨架。
DEFAULT_BLANK = [
    'cpp/主教材/章节学习/第01章 C++概述/我的作答/main.cpp',
    'cpp/主教材/章节学习/第01章 C++概述/课后习题/第11题 莱布尼茨级数估计π/work.cpp',
    'cpp/主教材/章节学习/第01章 C++概述/课后习题/第12题 中点矩形积分估计π/work.cpp',
    'cpp/主教材/章节学习/第02章 函数与库/我的作答/main.cpp',
    'cpp/主教材/章节学习/第02章 函数与库/课后习题/第14题 蒙特卡洛估计圆周率/work.cpp',
    'cpp/主教材/章节学习/第02章 函数与库/课后习题/第15题 连续三次正面/work.cpp',
    'cpp/主教材/章节学习/第03章 字符串类string/我的作答/main.cpp',
    'cpp/主教材/章节学习/第03章 字符串类string/课后习题/第19题 求逆置换密钥/work.cpp',
    'cpp/主教材/章节学习/第03章 字符串类string/课后习题/第20题 DNA互补链查找/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/我的作答/main.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第01题 三角函数格式化表格/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第02题 风寒指数二维表/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第03题 文件中的最长行/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第04题 文件行数、词数与字符数/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第11题 字符串与实数的严格转换/work.cpp',
    'cpp/主教材/章节学习/第04章 流类/课后习题/第12题 基于整行读取实现getReal与getLine/work.cpp',
    'cpp/主教材/章节学习/第05章 集合类/我的作答/main.cpp',
    'cpp/主教材/章节学习/第05章 集合类/课后习题/第18题 捕鼠夹与乒乓球离散仿真/work.cpp',
    'cpp/主教材/章节学习/第05章 集合类/课后习题/第19题 摩斯码与双向Map/work.cpp',
    'cpp/主教材/章节学习/第06章 类的设计/我的作答/main.cpp',
    'cpp/主教材/章节学习/第07章 递归简介/我的作答/main.cpp',
    'cpp/主教材/章节学习/第08章 递归策略/我的作答/main.cpp',
    'cpp/主教材/章节学习/第09章 回溯算法/我的作答/main.cpp',
    'cpp/主教材/章节学习/第10章 算法分析/我的作答/main.cpp',
    'cpp/主教材/章节学习/第11章 指针和数组/我的作答/main.cpp',
    'cpp/主教材/章节学习/第12章 动态内存管理/我的作答/main.cpp',
    'cpp/主教材/章节学习/第13章 效率和表示/我的作答/main.cpp',
    'cpp/主教材/章节学习/第14章 线性结构/我的作答/main.cpp',
    'cpp/主教材/章节学习/第15章 映射/我的作答/main.cpp',
    'cpp/主教材/章节学习/第16章 树/我的作答/main.cpp',
    'cpp/主教材/章节学习/第17章 集合/我的作答/main.cpp',
    'cpp/主教材/章节学习/第18章 图/我的作答/main.cpp',
    'cpp/主教材/章节学习/第19章 继承/我的作答/main.cpp',
    'cpp/主教材/章节学习/第20章 迭代策略/我的作答/main.cpp',
]


def load_modes():
    if MODES.is_file():
        return json.loads(MODES.read_text(encoding='utf-8'))
    return {}


def save_modes(modes):
    MODES.write_text(json.dumps(dict(sorted(modes.items())), ensure_ascii=False, indent=1) + '\n',
                     encoding='utf-8', newline='\n')


def header_of(text):
    """取题头注释块（到【本题说明结束】为止）。"""
    match = re.search(r'// 【本题说明开始】.*?' + re.escape(MARK), text, re.S)
    return match.group(0) if match else ''


def blank_text(text):
    header = header_of(text)
    if not header:
        return None
    # 题头里的“写在哪里”改成从零写的说法，其余保持
    header = re.sub(r'// 写在哪里：[^\n]*\n', '// 写在哪里：整份 work.cpp 都由你写，没有任何预置代码。\n', header)
    header = re.sub(r'// 实现什么：[^\n]*\n', '// 实现什么：从 include、函数到 main，全部自己写。\n', header)
    return header + '\n//\n// 在这里写你的完整程序。写完保存，再运行「本题：检查作答」。\n'


def template_path(work):
    rel = work.resolve().relative_to(ROOT.resolve()).with_suffix('.cpp')
    return TEMPLATE_DIR / rel


def has_code(text):
    """题头注释之外是否还有代码（从零写的文件只有注释）。"""
    body = re.sub(r'//[^\n]*', '', text)
    return bool(body.strip())


def switch(work, mode, dry=False):
    """mode: 'blank' 或 'guided'。返回一句结果说明。

    同一份作答有两条路径（数字名与带名字的目录指向同一文件），
    所以登记和备份都按解析后的真实路径算，否则会“说有、其实没有”。
    """
    work = work.resolve()
    text = work.read_text(encoding='utf-8')
    store = template_path(work)
    modes = load_modes()
    key = work.relative_to(ROOT.resolve()).as_posix()
    real = 'blank' if not has_code(text) else 'guided'
    current = modes.get(key, real)

    if mode == current and real == mode:
        return '已经是 %s，无需切换' % ('从零写' if mode == 'blank' else '引导版')

    if mode == 'blank':
        store.parent.mkdir(parents=True, exist_ok=True)
        if not store.exists():
            store.write_text(text, encoding='utf-8', newline='\n')
        new = blank_text(text)
        if new is None:
            return '这个文件没有题头，跳过'
        if not dry:
            work.write_text(new, encoding='utf-8', newline='\n')
            modes[key] = 'blank'
            save_modes(modes)
        if not dry:
            update_readme(work, 'blank')
        return '已切换为从零写；引导版存在 %s' % store.relative_to(ROOT).as_posix()

    # 切回引导版
    if not store.is_file():
        return '找不到引导版备份，无法切回'
    if not dry:
        shutil.copy2(store, work)
        modes.pop(key, None)
        save_modes(modes)
        update_readme(work, 'guided')
    return '已切回引导版'


MODE_BLOCK = '<!-- mode:start -->\n%s\n<!-- mode:end -->'
SAVED = '<!-- guided-section3\n%s\n-->'

BLANK_DOC = ('**当前模式：从零写。** 整份 `work.cpp` 由你写：没有补全区，也没有 `main` 骨架，'
             'include、函数、输入输出全由你安排。\n\n'
             '样例在 `input.txt` 与 `检查数据/` 里；写不动的时候可以点页面上的「要骨架」切回引导版，'
             '原文件会先备份。\n\n保存后运行任务“本题：检查作答”核对。')


def section3_range(text):
    return re.search(r'(##\s*3\s*·\s*写在哪里\s*\n\n)(.*?)(\n+##\s*4\s*·)', text, re.S)


def update_readme(work, mode):
    """切换后同步 README 第 3 段：当前模式的说明整段替换，原说明留在注释里以便切回。"""
    guide = work.parent / 'README.md'
    if not guide.is_file():
        return
    text = guide.read_text(encoding='utf-8')
    section = section3_range(text)
    if not section:
        return

    if mode == 'blank':
        if '<!-- mode:start -->' in text:
            return
        original = section.group(2)
        text = text[:section.start(2)] + (MODE_BLOCK % BLANK_DOC) + '\n\n' + (SAVED % original) + text[section.end(2):]
    else:
        if '<!-- mode:start -->' not in text:
            return
        saved = re.search(r'<!-- guided-section3\n(.*?)\n-->', text, re.S)
        body = saved.group(1) if saved else ''
        text = re.sub(r'<!-- mode:start -->.*?<!-- mode:end -->(\n\n<!-- guided-section3\n.*?\n-->)?',
                      body, text, count=1, flags=re.S)
    guide.write_text(text, encoding='utf-8', newline='\n')


def main():
    parser = argparse.ArgumentParser(description='切换引导版 / 从零写')
    parser.add_argument('target', nargs='?', help='work.cpp 路径，或题号片段（如 第03章/第20题）')
    parser.add_argument('--blank', action='store_true', help='切换为从零写')
    parser.add_argument('--guided', action='store_true', help='切回引导版')
    parser.add_argument('--list', action='store_true', help='列出当前从零写的题')
    parser.add_argument('--apply-default', action='store_true', help='把默认该从零写的题批量切过去')
    parser.add_argument('--resync', action='store_true', help='按真实路径重建模板与登记')
    args = parser.parse_args()

    if args.resync:
        # 把模板目录与模式登记都归一到真实路径；旧的数字名路径自动迁移
        moved = 0
        for old in list(TEMPLATE_DIR.rglob('*.cpp')):
            rel = old.relative_to(TEMPLATE_DIR).as_posix()
            work = (ROOT / rel)
            if not work.exists():
                continue
            new = template_path(work)
            if new != old:
                new.parent.mkdir(parents=True, exist_ok=True)
                shutil.move(str(old), str(new))
                moved += 1
        modes = {}
        for rel in DEFAULT_BLANK:
            work = (ROOT / rel)
            if not work.exists():
                continue
            work = work.resolve()
            if not has_code(work.read_text(encoding='utf-8')):
                modes[work.relative_to(ROOT.resolve()).as_posix()] = 'blank'
        save_modes(modes)
        for rel in modes:
            update_readme(ROOT / rel, 'blank')
        print('模板迁移 %d 份；登记 %d 题从零写' % (moved, len(modes)))
        return 0

    if args.list:
        modes = load_modes()
        print('当前从零写：%d 题' % len(modes))
        for key in sorted(modes):
            print('  -', key)
        return 0

    if args.apply_default:
        done = 0
        for rel in DEFAULT_BLANK:
            work = (ROOT / rel)
            if work.exists():
                note = switch(work, 'blank')
                if '已切换' in note:
                    done += 1
        print('切换 %d 题' % done)
        return 0

    if not args.target or not (args.blank or args.guided):
        parser.print_help()
        return 1

    target = args.target.replace('\\', '/')
    if target.endswith('.cpp'):
        work = ROOT / target
    else:
        # “第03章/第20题”这种片段要能匹配到带名字的目录：按段依次出现即可
        pattern = re.compile('.*'.join(re.escape(part) for part in target.split('/') if part))
        matches = list((ROOT / 'cpp/主教材/章节学习').rglob('work.cpp'))
        matches += list((ROOT / 'cpp/主教材/章节学习').rglob('我的作答/main.cpp'))
        found = [p for p in matches if pattern.search(p.relative_to(ROOT).as_posix())]
        work = found[0] if found else None
        if len(found) > 1:
            print('匹配到 %d 个，用第一个：%s' % (len(found), found[0].relative_to(ROOT).as_posix()))

    if not work or not work.is_file():
        print('找不到这份作答：', args.target)
        return 2
    print(switch(work, 'blank' if args.blank else 'guided'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
