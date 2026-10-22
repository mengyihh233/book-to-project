"""Preserve supplied EPUBs, validate paths and build an offline navigation page."""
from pathlib import Path,PurePosixPath
from html.parser import HTMLParser
import zipfile,xml.etree.ElementTree as ET,json,posixpath,shutil,html,hashlib,re
ROOT=Path('仓库根目录')
class CleanHTML(HTMLParser):
    def __init__(self):super().__init__(convert_charrefs=False);self.parts=[];self.skip=0
    def handle_starttag(self,tag,attrs):
        if tag in ('script','iframe','object','embed'):self.skip+=1;return
        if self.skip:return
        if tag=='base':return
        safe=[]
        for k,v in attrs:
            if k.lower().startswith('on'):continue
            if k in ('src','href') and v and re.match(r'(?i)\s*(javascript:|https?:|//)',v):continue
            safe.append((k,v))
        self.parts.append('<'+tag+''.join(' '+k+'="'+html.escape(v or '',quote=True)+'"' for k,v in safe)+'>')
    def handle_endtag(self,tag):
        if tag in ('script','iframe','object','embed'):
            self.skip=max(0,self.skip-1);return
        if not self.skip:self.parts.append('</'+tag+'>')
    def handle_data(self,data):
        if not self.skip:self.parts.append(data)
    def handle_entityref(self,name):
        if not self.skip:self.parts.append('&'+name+';')
    def handle_charref(self,name):
        if not self.skip:self.parts.append('&#'+name+';')

sources=[]
for key,pattern,label in [('cpp-five','C++之父*.epub','C++学习路线图（五册）'),('opengl','计算机图形学编程*.epub','OpenGL实践教材')]:
    source=next(Path('C:/Users/lsy08/Downloads').glob(pattern))
    dest=ROOT/'books'/f'{key}.epub';shutil.copy2(source,dest)
    target=ROOT/'reader'/key;target.mkdir(parents=True,exist_ok=True)
    with zipfile.ZipFile(dest) as z:
        container=ET.fromstring(z.read('META-INF/container.xml'))
        opf=container.find('.//{*}rootfile').attrib['full-path']
        package=ET.fromstring(z.read(opf))
        ncx=next(e.attrib['href'] for e in package.find('{*}manifest') if e.attrib.get('media-type')=='application/x-dtbncx+xml')
        nav_path=posixpath.normpath(posixpath.join(posixpath.dirname(opf),ncx))
        nav=ET.fromstring(z.read(nav_path));entries=[]
        def walk(items,depth=0):
            for n in items:
                if not n.tag.endswith('navPoint'):continue
                title=''.join(n.find('{*}navLabel').itertext()).strip()
                href=n.find('{*}content').attrib['src']
                href=posixpath.normpath(posixpath.join(posixpath.dirname(nav_path),href.split('#')[0]))+('#'+href.split('#',1)[1] if '#' in href else '')
                entries.append({'depth':depth,'title':title,'href':href})
                walk(list(n),depth+1)
        walk(list(nav.find('{*}navMap')))
        for info in z.infolist():
            name=PurePosixPath(info.filename)
            if name.is_absolute() or '..' in name.parts or ':' in info.filename:raise ValueError('Unsafe EPUB member')
            if info.is_dir():continue
            p=target/Path(*name.parts);p.parent.mkdir(parents=True,exist_ok=True)
            payload=z.read(info)
            if p.suffix.lower() in ('.html','.xhtml','.htm'):
                parser=CleanHTML();parser.feed(payload.decode('utf-8'));payload=''.join(parser.parts).encode('utf-8')
            if p.suffix.lower() in ('.js','.exe','.dll','.bat','.cmd'):continue
            p.write_bytes(payload)
        (ROOT/f'tools/{key}-toc.json').write_text(json.dumps(entries,ensure_ascii=False,indent=2),encoding='utf-8')
    sources.append({'key':key,'name':source.name,'source':str(source),'copy':str(dest),'sha256':hashlib.sha256(dest.read_bytes()).hexdigest(),'toc_entries':len(entries)})
    links=[]
    for e in entries:
        if e['depth']<=2:
            links.append(f'<a class="d{e["depth"]}" href="{html.escape(e["href"],quote=True)}" target="page">{html.escape(e["title"])}</a>')
    page=f'''<!doctype html><html lang="zh-CN"><meta charset="utf-8"><title>{label}</title>
<style>body{{margin:0;font:15px/1.6 system-ui,"Microsoft YaHei";display:flex;height:100vh}}nav{{width:320px;overflow:auto;background:#f3f5f8;padding:20px;box-sizing:border-box;flex-shrink:0}}a{{display:block;color:#234b74;text-decoration:none;padding:5px}}a:hover{{background:#dce7f1}}.d1{{padding-left:18px}}.d2{{padding-left:30px;font-size:13px}}iframe{{flex:1;border:0;background:white}}h1{{font-size:20px}}</style>
<nav><h1>{label}</h1><p>本地离线阅读；左侧选章节。需要搜索时在右侧正文按Ctrl+F。</p>{''.join(links)}</nav><iframe name="page" src="{entries[0]['href']}" title="书籍正文"></iframe></html>'''
    (target/'index.html').write_text(page,encoding='utf-8')
(ROOT/'tools/epub-sources.json').write_text(json.dumps(sources,ensure_ascii=False,indent=2),encoding='utf-8')
print('Both EPUBs preserved, extracted safely and indexed for offline reading.')
