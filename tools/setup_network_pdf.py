"""把《网络是怎样连接的》独立 PDF 接入 fundamentals 主线。

原四册 EPUB 中该册只有 HTML 内链；这份 PDF 提供可靠的页码引用，
与 linux / graphics 主线保持一致（既能跳转也能按页码查）。
同时把每章页码写回章节目录，供工作台展示。
"""
import json
import re
import shutil
from pathlib import Path

from pypdf import PdfReader

ROOT = Path('仓库根目录')
SRC = Path(r'D:\文件归档\下载整理-20261018-205822\01-PDF书籍资料\网络是怎样连接的 (户根勤) (z-library.sk, 1lib.sk, z-lib.sk).pdf')
DST = ROOT / 'books/network-how.pdf'


def main():
    if not (DST.exists() and DST.stat().st_size == SRC.stat().st_size):
        shutil.copy2(SRC, DST)
    print('PDF 已入库:', DST, DST.stat().st_size, '字节')

    reader = PdfReader(str(DST))
    pages = len(reader.pages)

    def walk(items, depth=0, out=None):
        if out is None:
            out = []
        for it in items:
            if isinstance(it, list):
                walk(it, depth + 1, out)
            else:
                try:
                    pg = reader.get_destination_page_number(it) + 1
                except Exception:
                    pg = None
                out.append({'depth': depth, 'title': str(it.title).strip(), 'pdf_page': pg})
        return out

    bookmarks = walk(reader.outline)
    chapters = []
    for b in bookmarks:
        m = re.match(r'^第\s*([0-9]+)\s*章\s*(.*)$', b['title'])
        if m and b['pdf_page']:
            chapters.append({'number': m.group(1), 'title': m.group(2).strip(), 'pdf_page': b['pdf_page']})
    print(f'共 {pages} 页，识别出 {len(chapters)} 章')

    # 写回 fundamentals-index.json，让每章都带上 PDF 页码
    idx_path = ROOT / 'tools/fundamentals-index.json'
    index = json.loads(idx_path.read_text(encoding='utf-8'))
    by_num = {c['number']: c['pdf_page'] for c in chapters}
    hit = 0
    for e in index:
        if e['book'].startswith('网络是怎样连接的'):
            pg = by_num.get(e['number'])
            if pg:
                e['pdf_page'] = pg
                hit += 1
    idx_path.write_text(json.dumps(index, ensure_ascii=False, indent=2), encoding='utf-8')
    print(f'已为 {hit} 章写入页码引用')

    record = {
        'key': 'network-how',
        'name': SRC.name,
        'source': str(SRC),
        'copy': str(DST),
        'pages': pages,
        'chapters': len(chapters),
    }
    books_json = ROOT / 'guide/当前教材清单.json'
    data = json.loads(books_json.read_text(encoding='utf-8')) if books_json.exists() else {}
    items = data.get('pdf', []) if isinstance(data, dict) else []
    items = [i for i in items if i.get('key') != 'network-how'] + [record]
    if isinstance(data, dict):
        data['pdf'] = items
    books_json.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding='utf-8')
    print('教材清单已更新')


if __name__ == '__main__':
    main()
