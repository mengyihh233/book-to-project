"""构建派生的按章阅读稿；不修改逐页校对源、学生代码或学习进度。"""
from pathlib import Path
import json,os,re

ROOT=Path(__file__).resolve().parents[1]
DATA=ROOT/'cpp/roberts/original'
CHAPTERS=ROOT/'cpp/主教材/章节学习'

def build():
    manifest=json.loads((DATA/'reader.json').read_text(encoding='utf-8-sig'))
    entries={p['pdf_page']:p for p in manifest['pages']}
    starts=[int(manifest['chapter_links'][str(c)]['chapter_page']) for c in range(1,21)]+[639]
    if starts!=sorted(set(starts)) or starts[0]!=16:
        raise ValueError('章节边界异常，先核对原文索引')
    results=[]
    for c in range(1,21):
        folder=CHAPTERS/f'第{c:02d}章'
        title=manifest['chapter_links'][str(c)]['title']
        first,last=starts[c-1],starts[c]-1
        questions=sum(int(entries[p].get('open_questions',0)) for p in range(first,last+1))
        def rel(p):return Path(os.path.relpath(p,folder)).as_posix()
        pdf=rel(ROOT/'books/cpp-roberts.pdf')
        viewer=rel(ROOT/'workbench/original.html')
        parts=[f'# {title} · 原书阅读\n\n'
               '[返回章节目录](../README.md) · [本章讲解与练习](README.md) · '
               '[我的核心作答](我的作答/main.cpp)\n\n'
               f'> 这份连续阅读稿来自逐页校对原文，覆盖PDF第{first}—{last}页，包含本章复习与原书习题。'
               '保留原页分界，不猜接跨页断句或代码。图文有疑问时点击“原页”核对扫描件；'
               f'本章登记待核对项{questions}处，细节见原页阅读器。中文讲解与参考答案从本章入口单独进入。\n\n'
               '> VS Code：打开本文件，按 Ctrl+Shift+V 预览；源码链接进入作答文件。'
               '如当前以网页方式阅读，可从专用章节阅读器使用目录与进度记忆。\n\n']
        image_count=0
        for p in range(first,last+1):
            if entries.get(p,{}).get('status')!='reviewed':
                raise ValueError(f'PDF {p} 尚未逐页校对，停止构建')
            text=(DATA/'pages'/f'{p:04d}.reviewed.md').read_text(encoding='utf-8-sig').strip()
            if not text:raise ValueError(f'PDF {p} 原文为空')
            def image(match):
                nonlocal image_count
                alt,name=match.groups()
                if not re.fullmatch(r'\d{4}\.fig-[a-z0-9-]+\.png',name):
                    raise ValueError(f'未识别的图示引用：{name}')
                source=DATA/'figures'/name
                if not source.is_file():raise FileNotFoundError(source)
                image_count+=1
                return f'![{alt}]({rel(source)})'
            text=re.sub(r'!\[(.*?)\]\(([^)]+\.png)\)',image,text)
            parts.append(f'###### [原页 · PDF {p}]({viewer}#page={p})\n\n{text}\n\n')
        parts.append(f'---\n\n[回到本章讲解与练习](README.md) · [原版PDF]({pdf}#page={first})\n')
        out=folder/'原书阅读.md'
        value=''.join(parts)
        if not out.exists() or out.read_text(encoding='utf-8')!=value:
            temp=out.with_suffix('.tmp');temp.write_text(value,encoding='utf-8');temp.replace(out)
        results.append({'chapter':c,'pages':[first,last],'images':image_count,'open_questions':questions,'path':out.relative_to(ROOT).as_posix()})
    return results

if __name__=='__main__':
    results=build()
    print(json.dumps({'chapters':len(results),'pages':sum(r['pages'][1]-r['pages'][0]+1 for r in results),'images':sum(r['images'] for r in results),'results':results},ensure_ascii=False,indent=2))
