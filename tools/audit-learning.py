"""只读检查教材、参考源、工作区、作答入口与本地文档链接。"""
from pathlib import Path
import json,re,hashlib,time,os
from urllib.parse import urlsplit,unquote
ROOT=Path(__file__).resolve().parent.parent
def main():
    manifest=json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8'))
    book=json.loads((ROOT/'tools/book-tests.json').read_text(encoding='utf-8'))
    missing=[];links=[];hashes={}
    for item in manifest+book:
        p=ROOT/item['source']
        if not p.is_file():missing.append(item['source']);continue
        hashes[item['id']]=hashlib.sha256(p.read_bytes()).hexdigest()
    ws=json.loads((ROOT/'学习工作区.code-workspace').read_text(encoding='utf-8'))
    for folder in ws['folders']:
        if not (ROOT/folder['path']).is_dir():missing.append(folder['path'])
    # 中文目录联接仅提供入口；审计每个真实目录一次，避免重复扫描与联接循环。
    documents=[]
    excluded={'archive','vendor','reader','build','.remote-vscode','.remote-vscode-cli','.git','__pycache__'}
    for folder,dirs,files in os.walk(ROOT,followlinks=False):
        dirs[:]=[name for name in dirs if name not in excluded and not (Path(folder)/name).is_symlink() and not (Path(folder)/name).is_junction()]
        documents.extend(Path(folder)/name for name in files if name.endswith('.md'))
    for p in documents:
        text=p.read_text(encoding='utf-8')
        # C++的operator[](int k)不是Markdown链接。
        text=re.sub(r'^\s*(`{3,}|~{3,})[^\n]*\n.*?^\s*\1\s*$','',text,flags=re.S|re.M)
        text=re.sub(r'(`+).*?\1','',text)
        for link in re.findall(r'\]\(([^)]+)\)',text):
            url=urlsplit(link)
            if url.scheme or not url.path:continue
            name=unquote(url.path)
            target=ROOT/name.lstrip('/') if name.startswith('/') else p.parent/name
            # Original-page Markdown uses figure IDs resolved by original.js
            # through /api/original/figure; verify the backing file, not pages/.
            if p.is_relative_to(ROOT/'cpp/roberts/original/pages') and re.fullmatch(r'\d{4}\.fig-[a-z0-9-]+\.png',name):
                target=ROOT/'cpp/roberts/original/figures'/name
            if not target.exists():links.append({'file':str(p.relative_to(ROOT)),'target':link})
    result={'checked_at':time.strftime('%Y-%m-%d %H:%M:%S'),'chapter_labs':len(manifest),'book_exercises':len(book),'book_cases':sum(len(e['cases']) for e in book),'missing_files':missing,'broken_links':links,'reference_sha256':hashes}
    (ROOT/'guide/学习区审计.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    print(f'章节配套题{len(manifest)}道，原书已解编程题{len(book)}道，验收样例{result["book_cases"]}组。')
    print(f'缺失文件{len(missing)}个，失效链接{len(links)}个。')
    return 1 if missing or links else 0
if __name__=='__main__':raise SystemExit(main())
