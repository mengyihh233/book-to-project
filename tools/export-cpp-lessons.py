"""把工作台小课数据导出为同一套可离线阅读的Markdown；不改学生作答。"""
from pathlib import Path
import os,json
ROOT=Path(__file__).resolve().parents[1]
data=json.loads((ROOT/'workbench/cpp-lessons.json').read_text(encoding='utf-8'))
folder=ROOT/'cpp/语法小课';answers=folder/'提示与答案';answers.mkdir(parents=True,exist_ok=True)
for n,title in enumerate(data['groups'],1):
    units=[e for e in data['lessons'] if e['group']==n]
    rel=lambda path:Path(os.path.relpath(ROOT/path,folder)).as_posix()
    parts=[f'# {title}\n\n[小课目录](README.md) · [网页小课](../../workbench/cpp-tutorial.html)\n\n']
    answer=[f'# {title}：提示与答案\n\n[回本组教程](../{n:02d}-{title}.md)\n\n先做练习，再核对。小测答案不代替实际程序验收。\n\n']
    for e in units:
        source=e.get('book_source');origin=''
        if source:
            url='../../workbench/chapter.html?chapter='+str(source['chapter'])+('#page='+str(source['pdf_page']) if source.get('pdf_page') else '')
            origin=f'原书联系：[{source["title"]}]({url})。{source["note"]}\n\n'
        parts += [f'## {e["title"]}'+('（按需补充）' if e.get('level')=='supplement' else '')+'\n\n',origin,'\n\n'.join(e['explain'])+'\n\n',f'```cpp\n{e["code"]}```\n\n',f'### 先预测\n\n{e["quiz"]["prompt"]}\n\n']
        if e.get('pitfall'):parts.insert(len(parts)-1,'**容易混淆：** '+e['pitfall']+'\n\n')
        parts += [f'{i+1}. {o}\n' for i,o in enumerate(e['quiz']['options'])]
        if e.get('fill'):
            parts += [f'\n### 代码填空\n\n{e["fill"]["prompt"]}\n\n```cpp\n{e["fill"]["snippet"]}\n```\n\n']
        parts += [f'\n### 动手练\n\n{e["practice"]["instruction"]}\n\n[自己的作答]({rel(e["practice"]["path"])}) · [关联练习说明]({rel(e["practice"]["guide"])})\n\n']
        if e['practice'].get('focus'):parts.append('修改位置：'+e['practice']['focus']+'\n\n')
        if e['practice'].get('steps'):
            parts.append('从这里下手：\n\n')
            parts += [f'{i+1}. {step}\n' for i,step in enumerate(e['practice']['steps'])]
            parts.append('\n')
        parts += ['- '+check+'\n' for check in e['practice'].get('checks',[])]
        if e['practice'].get('stdin'):parts.append('\n启动程序后再输入（不要写进源码）：\n\n```text\n'+e['practice']['stdin']+'\n```\n\n')
        parts.append(f'\n做完再看：[本组提示与答案](提示与答案/{n:02d}.md)\n\n---\n\n')
        answer += [f'## {e["title"]}\n\n提示：{e["hint"]}\n\n小测：{e["quiz"]["answer"]+1}。{e["quiz"]["reason"]}\n\n示例约定环境的输出：\n\n```text\n{e["output"]}```\n\n']
        if e.get('fill'):answer.append('代码填空：'+ ' 或 '.join('`'+a+'`' for a in e['fill']['accepted'])+'。'+e['fill']['reason']+'\n\n')
        if e['practice'].get('model'):
            m=next(m for m in data['practice_models'] if m['id']==e['practice']['model'])
            answer.append(f'实操对照：[{m["title"]}](整合实操参考.md#model-{m["id"]})。按本节修改位置取用相关片段，保留原作答。\n\n')
    if n<=2:
        reference='基础语法参考.cpp' if n==1 else '流程与函数参考.cpp'
        answer.append(f'\n## 配套实操参考\n\n[本组完整参考实现]({reference}) · [输入与预期结果](README.md)\n\n先完成自己的代码，再核对；其余练习沿用原题解析。\n')
    (folder/f'{n:02d}-{title}.md').write_text(''.join(parts),encoding='utf-8')
    (answers/f'{n:02d}.md').write_text(''.join(answer),encoding='utf-8')
guide=['# 基本概念：先理解，再写代码\n\n[小课目录](README.md) · [网页小课](../../workbench/cpp-tutorial.html)\n\n以下是依据原书核心主题的中文提炼，示例与练习为配套原创。\n\n## 从原书挑出的五条主线\n\n']
guide += ['- '+s+'\n' for s in data.get('core_summary',[])]
guide.append('\n## 概念速查\n\n| 概念 | 怎么理解 | 去学与练 |\n|---|---|---|\n')
for c in data.get('concepts',[]):
    e=next(e for e in data['lessons'] if e['id']==c['lesson']);title=data['groups'][e['group']-1]
    guide.append(f'| {c["term"]} | {c["definition"]} | [{e["title"]}]({e["group"]:02d}-{title}.md) |\n')
(folder/'基本概念速查.md').write_text(''.join(guide),encoding='utf-8')
models=['# 整合实操参考\n\n[回小课目录](../README.md)\n\n先自己写，再核对。以下每份是独立程序；融入现有作答时按本节定位取用片段，不能直接追加第二个main。输出为本参考程序的完整输出；原作答保留其他题目时可能有额外输出。\n\n']
for m in data.get('practice_models',[]):
    models.append(f'<a id="model-{m["id"]}"></a>\n\n## {m["title"]}\n\n{m["note"]}\n\n```cpp\n{m["code"]}```\n\n预期输出：\n\n```text\n{m["output"]}```\n\n')
(answers/'整合实操参考.md').write_text(''.join(models),encoding='utf-8')
print(f'exported {len(data["groups"])} tutorial/answer groups and concept guide; no student code changed')
