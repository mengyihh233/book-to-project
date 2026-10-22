"""导入你自己合法持有的教材副本。

仓库里不含任何原书内容。这个工具只做搬运和校验：
把书放进 books/，把某章文字稿放进对应章目录，让工作台和检查器能找到它们。

用法：
    python tools/import-book.py --list
    python tools/import-book.py --check
    python tools/import-book.py cpp-roberts "D:/我的书/C++程序设计.pdf"
    python tools/import-book.py cpp-roberts --text "D:/第2章.txt" --chapter 2
    python tools/import-book.py cpp-roberts --text "D:/第2章.md" --chapter 2 --force
"""
from pathlib import Path
import argparse
import json
import shutil
import sys

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / 'tools/book-manifest.json'


def load():
    return json.loads(MANIFEST.read_text(encoding='utf-8'))


def fmt_size(num):
    for unit in ('B', 'KB', 'MB', 'GB'):
        if num < 1024 or unit == 'GB':
            return '%.1f %s' % (num, unit)
        num /= 1024


def show_list(data):
    print('书单（本仓库不含任何原书内容，请自行准备合法副本）\n')
    have = miss = 0
    for book in data['books']:
        target = ROOT / book['target']
        exists = target.is_file()
        have += exists
        miss += not exists
        mark = '已导入' if exists else ('缺失·必需' if book['required'] else '缺失·可选')
        size = '（%s）' % fmt_size(target.stat().st_size) if exists else ''
        print('%-18s %-9s %s%s' % (book['id'], mark, book['title'], size))
        print('%-18s 用于：%s' % ('', book['used_by']))
    print('\n已导入 %d 本，缺失 %d 本。' % (have, miss))
    print('导入：python tools/import-book.py <id> "<你的文件路径>"')


def check(data):
    missing = [b for b in data['books'] if b['required'] and not (ROOT / b['target']).is_file()]
    if not missing:
        print('必需教材都已就位。')
        return 0
    print('还缺 %d 本必需教材：' % len(missing))
    for book in missing:
        print('  %-18s %s' % (book['id'], book['title']))
    print('\n导入示例：python tools/import-book.py %s "<你的文件路径>"' % missing[0]['id'])
    return 1


def copy_file(src, target, force):
    if not src.is_file():
        return '找不到文件：%s' % src
    if target.exists() and not force:
        return '目标已存在，未覆盖：%s（要覆盖请加 --force）' % target.relative_to(ROOT)
    target.parent.mkdir(parents=True, exist_ok=True)
    size = src.stat().st_size
    if size > 50 * 1024 * 1024:
        print('正在复制 %s …' % fmt_size(size))
    shutil.copy2(src, target)
    return '已导入 %s（%s）' % (target.relative_to(ROOT), fmt_size(size))


def import_book(data, book_id, src_path, force):
    book = next((b for b in data['books'] if b['id'] == book_id), None)
    if not book:
        return '没有这本书：%s。用 --list 查看可用的 id。' % book_id
    src = Path(src_path)
    if src.suffix.lower() not in book['accept']:
        return '格式不符：这本书接受 %s，你给的是 %s' % ('/'.join(book['accept']), src.suffix or '（无扩展名）')
    return copy_file(src, ROOT / book['target'], force)


def import_text(data, chapter, src_path, force):
    src = Path(src_path)
    if not src.is_file():
        return '找不到文件：%s' % src
    if src.suffix.lower() not in ('.md', '.txt'):
        return '文字稿请给 .md 或 .txt，你给的是 %s' % (src.suffix or '（无扩展名）')
    folder = ROOT / ('cpp/主教材/章节学习/第%02d章' % chapter)
    if not folder.is_dir():
        return '没有第 %d 章目录：%s' % (chapter, folder.relative_to(ROOT))
    target = folder / '原书阅读.md'
    if target.exists() and not force:
        return '这一章已有文字稿，未覆盖：%s（要覆盖请加 --force）' % target.relative_to(ROOT)
    text = src.read_text(encoding='utf-8', errors='replace')
    if src.suffix.lower() == '.txt':
        # 纯文本补一个标题，阅读页才能显示章名。
        title = folder.name
        text = '# %s · 原书阅读\n\n> 本文件由 import-book.py 从你自己的文字稿导入。\n\n%s' % (title, text)
    target.write_text(text, encoding='utf-8', newline='\n')
    return '已导入第 %d 章文字稿（%d 字）：%s' % (chapter, len(text), target.relative_to(ROOT))


def main():
    parser = argparse.ArgumentParser(description='导入你合法持有的教材副本')
    parser.add_argument('book', nargs='?', help='书籍 id，见 --list')
    parser.add_argument('file', nargs='?', help='你的文件路径')
    parser.add_argument('--list', action='store_true', help='列出书单与状态')
    parser.add_argument('--check', action='store_true', help='只检查必需教材是否齐全')
    parser.add_argument('--text', help='导入某章文字稿（配合 --chapter）')
    parser.add_argument('--chapter', type=int, help='章号，例如 2')
    parser.add_argument('--force', action='store_true', help='允许覆盖已有文件')
    args = parser.parse_args()

    data = load()
    if args.list or (not args.book and not args.check):
        show_list(data)
        return 0
    if args.check:
        return check(data)

    if args.text:
        if not args.chapter:
            print('导入文字稿需要同时给 --chapter，例如 --chapter 2')
            return 2
        print(import_text(data, args.chapter, args.text, args.force))
        return 0

    if not args.file:
        print('请给出文件路径，例如：python tools/import-book.py %s "D:/书.pdf"' % args.book)
        return 2
    print(import_book(data, args.book, args.file, args.force))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
