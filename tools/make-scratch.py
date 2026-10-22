"""为每道课后习题生成一份「从零写」作答文件。

同一道题保留两个并列的作答入口，互不覆盖：

- `work.cpp`        补充型：main 与辅助函数已给出，只补补全区（网页上就是这个）
- `from-scratch.cpp` 从零写：只有题头，include / 函数 / main 全部自己写
- `reference.cpp`    参考答案（工作区里隐藏）

两份都跑同一组登记样例，所以都能判分。
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path('仓库根目录')
THROW = '// 本题是「从零写」：没有骨架，也没有补全区。'
WHERE = '// 写在哪里：本文件，从第一行 #include 开始全部自己写。'


def header_of(text):
    m = re.search(r'// 【本题说明开始】[\s\S]*?// 【本题说明结束】', text)
    return m.group(0) if m else ''


def make_scratch(work_text):
    header = header_of(work_text)
    if not header:
        return None
    # 原题头写的是“在 BEGIN 1 到 END 1 之间补全”，从零写要换掉这句
    header = re.sub(r'^// 写在哪里：.*$', WHERE, header, flags=re.M)
    if WHERE not in header:
        header = header.replace('// 【本题说明结束】', WHERE + '\n// 【本题说明结束】')
    # “读入已给出、中间留空”是针对补写版的描述，从零写里不存在这回事；
    # 但如果这一行写的是函数签名（如 bool isPrime(int n)），要保留，那是接口约定。
    header = re.sub(
        r'^// 实现什么：.*(?:整段由你写|已给出).*$',
        '// 实现什么：整段由你写：include、读入、计算、输出、错误处理全部自己安排。',
        header, flags=re.M)
    return header + '\n\n' + THROW + '\n// 参考实现与补写版在同一目录；卡住 20 分钟再看。\n'


def main():
    write = '--write' in sys.argv
    cards = json.loads((ROOT / 'tools/answer-cards.json').read_text(encoding='utf-8'))
    made = skipped = 0
    samples = []
    for c in cards:
        work = ROOT / c['work']
        if not work.is_file():
            continue
        # 只处理 C++ 课后习题；章内练习和综合项目另行处理
        if '/课后习题/' not in c['work'] or not c['work'].endswith('work.cpp'):
            continue
        if c.get('check') not in ('book', 'svg'):
            continue
        text = make_scratch(work.read_text(encoding='utf-8', errors='replace'))
        if not text:
            skipped += 1
            continue
        target = work.parent / 'from-scratch.cpp'
        if write:
            target.write_text(text, encoding='utf-8', newline='\n')
        made += 1
        if len(samples) < 2:
            samples.append((str(target.relative_to(ROOT)), text))

    print('生成 from-scratch.cpp:', made, '｜跳过（无题头）:', skipped, '｜写盘:', write)
    for name, text in samples:
        print('---', name)
        print('\n'.join(text.split('\n')[:8]))


if __name__ == '__main__':
    main()
