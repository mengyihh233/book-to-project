"""用**没登记过**的输入对照参考实现，防止对着样例硬凑。

做法是差分测试：
  1. 取本题已登记的输入，做小幅变异（改数字、改字母大小写、加一位、删一位）；
  2. 同一份输入，分别喂给参考实现和你的作答；
  3. 退出码与标准输出必须一致。

变异的输入不在登记样例里，所以「背答案」过不了这一关。
"""
import argparse
import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'tools'))

import study  # noqa: E402
from answer_compare import matches  # noqa: E402
from file_cases import case_directory  # noqa: E402
from multifile import companion_sources  # noqa: E402
from scaffold_state import source_template_reason  # noqa: E402


def load_item(source):
    import json
    tests = json.loads((ROOT / 'tools/book-tests.json').read_text(encoding='utf-8'))
    return next((e for e in tests if (ROOT / e['source']).parent.resolve() == source.parent), None)


def mutate_int(text, rng):
    try:
        value = int(text)
    except ValueError:
        return None
    delta = rng.choice([-3, -1, 1, 2, 5])
    return str(value + delta)


def mutate_float(text, rng):
    try:
        value = float(text)
    except ValueError:
        return None
    if value.is_integer() and abs(value) < 1e6:
        return str(value + rng.choice([-2, -1, 1, 3]))
    return '%.6g' % (value * rng.choice([1.5, 0.5, 2.0]))


def mutate_word(text, rng):
    if not text:
        return None
    # 只保护少数几个关键字，别把 DNA 这种大写数据也跳过了
    if text.strip().upper() in {'ALL', 'DEFAULT'}:
        return None
    if text.isalpha():
        pick = rng.choice(['swap', 'append', 'trim'])
        if pick == 'swap':
            return text.swapcase()
        if pick == 'append':
            return text + rng.choice(['x', 'Z'])
        return text[:-1] or None
    return None


def mutate(text, rng):
    """逐行尝试小幅改动；改不动就返回 None。"""
    lines = text.split('\n')
    changed = False
    for index, line in enumerate(lines):
        if not line.strip():
            continue
        for rule in (mutate_int, mutate_float, mutate_word):
            new = rule(line, rng)
            if new is not None and new != line:
                lines[index] = new
                changed = True
                break
    return '\n'.join(lines) if changed else None


def variants(item, count, seed):
    rng = random.Random(seed)
    pool = []
    for case in item['cases']:
        inp = case[0] if isinstance(case, (list, tuple)) else case
        for _ in range(4):
            new = mutate(inp, rng)
            if new and new != inp and new not in pool:
                pool.append(new)
            if len(pool) >= count:
                return pool
    return pool[:count]


def normalise(out, item):
    text = out if item.get('preserve_all_output') else (out.removesuffix('\n') if item.get('preserve_output') else out.strip())
    if item.get('last_line'):
        text = text.splitlines()[-1] if text else ''
    return text


def run(exe, inp, item, folder_root):
    with case_directory(item, folder_root) as folder:
        result = study.call([exe], input=inp, capture_output=True, text=True, timeout=10, cwd=folder)
    return result.returncode, normalise(result.stdout, item)


def main():
    parser = argparse.ArgumentParser(description='用没登记过的输入对照参考实现')
    parser.add_argument('source', help='你的作答 work.cpp')
    parser.add_argument('--count', type=int, default=3, help='生成几组隐藏输入')
    parser.add_argument('--seed', type=int, default=20261022)
    args = parser.parse_args()

    source = study.valid_source(args.source, ('.cpp', '.c'))
    item = load_item(source)
    if item is None:
        print('本题没有登记样例，无法生成隐藏输入。')
        return 2
    reference = source.parent / 'reference.cpp'
    if not reference.is_file():
        print('本题没有参考实现，无法做差分检查。')
        return 2
    try:
        if companion_sources(ROOT, source):
            print('多文件题暂不支持隐藏样例检查。')
            return 2
    except ValueError:
        pass

    reason = source_template_reason(ROOT, source)
    if reason:
        print('还没开始写：' + reason)
        print('先写出自己的实现，再来测隐藏样例。')
        return 3
    try:
        mine = study.build(source)
        theirs = study.build(reference)
    except Exception:
        print('编译失败，先让程序能编译再测隐藏样例。')
        return 4

    cases = variants(item, args.count, args.seed)
    if not cases:
        print('这题登记的都是空输入，生成不出变体。')
        return 2

    print('用 %d 组没登记的输入对照参考实现：' % len(cases))
    agree = 0
    for index, inp in enumerate(cases, 1):
        try:
            ref_code, ref_out = run(theirs, inp, item, source.parent)
            my_code, my_out = run(mine, inp, item, source.parent)
        except Exception as error:
            print('隐藏样例%d：执行失败（%s）' % (index, error))
            continue
        ok = my_code == ref_code and matches(my_out, ref_out, item)
        agree += ok
        print('隐藏样例%d：%s' % (index, '一致' if ok else '不一致'))
        if not ok:
            print('  输入：%r' % inp)
            print('  参考：%r（退出码 %d）' % (ref_out, ref_code))
            print('  你的：%r（退出码 %d）' % (my_out, my_code))
    print('一致 %d/%d。' % (agree, len(cases)))
    if agree != len(cases):
        print('不一致不代表你一定错，也不代表对：说明你的程序和参考实现在这组输入上行为不同，先想清楚哪种才是题目要求。')
        return 1
    print('这些输入你没有见过，行为一致说明不是照着样例凑出来的。')
    return 0


if __name__ == '__main__':
    sys.exit(main())
