"""为图灵经典计算机基础系列（四册）建立离线阅读器与章节目录。

沿用 setup_epubs.py 的安全解压策略：剔除脚本与可执行文件、清理内联事件、
拒绝越界路径，确保离线页面不会执行原书携带的脚本。
"""
import json
import posixpath
import xml.etree.ElementTree as ET
import zipfile
from html.parser import HTMLParser
from pathlib import Path, PurePosixPath
import hashlib
import html
import re

ROOT = Path('仓库根目录')
KEY = 'fundamentals'
LABEL = '图灵经典计算机基础（四册）'
BOOK = ROOT / 'books/fundamentals-four.epub'
TARGET = ROOT / 'reader' / KEY


class CleanHTML(HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=False)
        self.parts = []
        self.skip = 0

    def handle_starttag(self, tag, attrs):
        if tag in ('script', 'iframe', 'object', 'embed'):
            self.skip += 1
            return
        if self.skip:
            return
        if tag == 'base':
            return
        safe = []
        for k, v in attrs:
            if k.lower().startswith('on'):
                continue
            if k in ('src', 'href') and v and re.match(r'(?i)\s*(javascript:|https?:|//)', v):
                continue
            safe.append((k, v))
        self.parts.append('<' + tag + ''.join(' ' + k + '="' + html.escape(v or '', quote=True) + '"' for k, v in safe) + '>')

    def handle_endtag(self, tag):
        if tag in ('script', 'iframe', 'object', 'embed'):
            self.skip = max(0, self.skip - 1)
            return
        if not self.skip:
            self.parts.append('</' + tag + '>')

    def handle_data(self, data):
        if not self.skip:
            self.parts.append(data)

    def handle_entityref(self, name):
        if not self.skip:
            self.parts.append('&' + name + ';')

    def handle_charref(self, name):
        if not self.skip:
            self.parts.append('&#' + name + ';')


def main():
    TARGET.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(BOOK) as z:
        container = ET.fromstring(z.read('META-INF/container.xml'))
        opf = container.find('.//{*}rootfile').attrib['full-path']
        package = ET.fromstring(z.read(opf))
        ncx = next(e.attrib['href'] for e in package.find('{*}manifest')
                   if e.attrib.get('media-type') == 'application/x-dtbncx+xml')
        nav_path = posixpath.normpath(posixpath.join(posixpath.dirname(opf), ncx))
        nav = ET.fromstring(z.read(nav_path))

        entries = []

        def walk(items, depth=0):
            for n in items:
                if not n.tag.endswith('navPoint'):
                    continue
                title = ''.join(n.find('{*}navLabel').itertext()).strip()
                src = n.find('{*}content').attrib['src']
                base = posixpath.normpath(posixpath.join(posixpath.dirname(nav_path), src.split('#')[0]))
                href = base + ('#' + src.split('#', 1)[1] if '#' in src else '')
                entries.append({'depth': depth, 'title': title, 'href': href})
                walk(list(n), depth + 1)

        walk(list(nav.find('{*}navMap')))

        # 套装4册的顶层书名（depth 0 且不在"版权/前言/后记"之列）
        BOOKS = ['计算机是怎样跑起来的', '程序是怎样跑起来的',
                 '面向对象是怎样工作的', '网络是怎样连接的']
        current = None
        books = []
        for e in entries:
            if e['depth'] == 0 and any(b[:6] in e['title'] for b in BOOKS):
                current = {'name': e['title'], 'href': e['href'], 'chapters': []}
                books.append(current)
                continue
            if current is None:
                continue
            m = re.match(r'^\s*第\s*([0-9]+|[一二三四五六七八九十]+)\s*章\s*(.+)$', e['title'])
            if m:
                e['book'] = current['name']
                e['number'] = m.group(1)
                e['chapter_title'] = m.group(2).strip()
                current['chapters'].append(e)

        for info in z.infolist():
            name = PurePosixPath(info.filename)
            if name.is_absolute() or '..' in name.parts or ':' in info.filename:
                raise ValueError('Unsafe EPUB member')
            if info.is_dir():
                continue
            p = TARGET / Path(*name.parts)
            p.parent.mkdir(parents=True, exist_ok=True)
            payload = z.read(info)
            if p.suffix.lower() in ('.html', '.xhtml', '.htm'):
                parser = CleanHTML()
                parser.feed(payload.decode('utf-8'))
                payload = ''.join(parser.parts).encode('utf-8')
            if p.suffix.lower() in ('.js', '.exe', '.dll', '.bat', '.cmd'):
                continue
            p.write_bytes(payload)

    total = sum(len(b['chapters']) for b in books)
    (ROOT / f'tools/{KEY}-toc.json').write_text(
        json.dumps({'books': books, 'total_chapters': total}, ensure_ascii=False, indent=2), encoding='utf-8')

    links = []
    for b in books:
        links.append(f'<a class="book" href="{html.escape(b["href"], quote=True)}" target="page">{html.escape(b["name"])}</a>')
        for c in b['chapters']:
            links.append(f'<a class="d1" href="{html.escape(c["href"], quote=True)}" target="page">第{c["number"]}章　{html.escape(c["chapter_title"])}</a>')

    page = f'''<!doctype html><html lang="zh-CN"><meta charset="utf-8"><title>{LABEL}</title>
<style>body{{margin:0;font:15px/1.6 system-ui,"Microsoft YaHei";display:flex;height:100vh;background:#f3f5f8}}nav{{width:340px;overflow:auto;background:#f3f5f8;padding:20px;box-sizing:border-box;flex-shrink:0}}a{{display:block;color:#234b74;text-decoration:none;padding:5px;border-radius:4px}}a:hover{{background:#dce7f1}}a.book{{font-weight:700;color:#12324f;margin-top:14px;border-left:3px solid #234b74;padding-left:10px}}.d1{{padding-left:22px;font-size:14px}}iframe{{flex:1;border:0;background:white}}h1{{font-size:20px;margin:0 0 6px}}p{{font-size:13px;color:#567;margin:0 0 14px}}</style>
<nav><h1>{LABEL}</h1><p>本地离线阅读，共 {len(books)} 册 {total} 章。左侧选章节，正文内按 Ctrl+F 搜索。</p>{''.join(links)}</nav><iframe name="page" src="{books[0]['href']}" title="书籍正文"></iframe></html>'''
    (TARGET / 'index.html').write_text(page, encoding='utf-8')

    record = {'key': KEY, 'name': BOOK.name, 'copy': str(BOOK),
              'sha256': hashlib.sha256(BOOK.read_bytes()).hexdigest(),
              'books': [{'name': b['name'], 'chapters': len(b['chapters'])} for b in books],
              'total_chapters': total}
    records = json.loads((ROOT / 'tools/epub-sources.json').read_text(encoding='utf-8'))
    records = [r for r in records if r.get('key') != KEY] + [record]
    (ROOT / 'tools/epub-sources.json').write_text(json.dumps(records, ensure_ascii=False, indent=2), encoding='utf-8')

    for b in books:
        print(f"{b['name']}: {len(b['chapters'])} 章")
    print(f'合计 {total} 章；离线阅读器 reader/{KEY}/index.html 已生成')


if __name__ == '__main__':
    main()
