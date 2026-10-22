"""恢复Roberts主教材与20章入口；不覆盖已有作答，不删除PPP参考内容。"""
from pathlib import Path
import shutil,hashlib,json,csv,re
R=Path(__file__).resolve().parents[1]
book=R/'books/cpp-roberts.pdf'
if not book.exists():shutil.copy2(R/'books/archive/cpp-roberts.pdf',book)
outline=json.loads((R/'tools/cpp-outline.json').read_text(encoding='utf-8'))
chapters=[];current=None
for e in outline:
 if re.match(r'^第\d+章',e['title']):
  current={'number':len(chapters)+1,'title':e['title'],'pdf_page':e['pdf_page']};chapters.append(current)
 elif current and e['title'] in ('复习题','习题'):current['review_page' if e['title']=='复习题' else 'exercise_page']=e['pdf_page']
with (R/'guide/学习进度.csv').open(encoding='utf-8-sig',newline='') as f:rows=list(csv.DictReader(f))
index=[]
for ch in chapters:
 n=ch['number'];src=R/f'archive/cpp-roberts/chapters/ch{n:02}';dest=R/f'cpp/主教材/章节学习/ch{n:02}'
 if not dest.exists():shutil.copytree(src,dest)
 (dest/'原书题目.md').write_text(f"# {ch['title']}：原书任务入口\n\n[本章教材](../../../../books/cpp-roberts.pdf#page={ch['pdf_page']}) · [复习题](../../../../books/cpp-roberts.pdf#page={ch['review_page']}) · [课后习题](../../../../books/cpp-roberts.pdf#page={ch['exercise_page']})\n\n页码均为PDF页码，不是纸书页码。\n\n复习题在work/answers.md作答；编程题在work/exNN.cpp中实现。配套reference.cpp不等于整章原书习题答案。已解的第1章习题见cpp/主教材/章节学习/第01章 C++概述/课后习题。\n",encoding='utf-8')
 ident=f'ROB-L{n:02}';index.append(dict(id=ident,title=ch['title'],folder=dest.relative_to(R).as_posix(),book='books/cpp-roberts.pdf',**{k:v for k,v in ch.items() if k!='title'}))
 if not any(x['题号']==ident for x in rows):
  with (R/'guide/学习进度.csv').open('a',encoding='utf-8',newline='') as f:csv.DictWriter(f,fieldnames=list(rows[0])).writerow(dict(zip(rows[0],[ident,'配套练习','未开始','','',''])))
(R/'tools/roberts-index.json').write_text(json.dumps(index,ensure_ascii=False,indent=2),encoding='utf-8')
(R/'guide/当前C++主教材.json').write_text(json.dumps({'book':'books/cpp-roberts.pdf','sha256':hashlib.sha256(book.read_bytes()).hexdigest(),'chapters':20,'priority':'用户2026-10-19明确指定；PPP五册保留为参考'},ensure_ascii=False,indent=2),encoding='utf-8')
print('Roberts:20 chapters, PDF retained locally, work preserved.')
