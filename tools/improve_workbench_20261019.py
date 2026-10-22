"""单次界面迁移；不修改学习作答和进度。"""
from pathlib import Path
R=Path(__file__).resolve().parents[1]
p=R/'workbench/index.html';s=p.read_text(encoding='utf-8')
s=s.replace('<body>','<body data-theme="dark">').replace('<strong>5</strong>','<strong id="track-count">—</strong>')
s=s.replace('五条学习主线，一张清晰的书桌。','九条学习主线，一张清晰的书桌。')
s=s.replace('<a href="/guide/开始学习.md"','<button id="theme" aria-label="切换明暗主题">切换浅色</button><a href="/guide/开始学习.md"',1)
s=s.replace('<section id="overview">','<section id="resume" class="route" hidden></section><section id="overview">')
s=s.replace('<pre id="doc"></pre>','<pre id="doc"></pre><div class="actions" id="doc-links"></div><p class="muted" id="scope"></p><div class="actions" id="chapter-files"></div>')
p.write_text(s,encoding='utf-8')
p=R/'workbench/app.js';s=p.read_text(encoding='utf-8')
s=s.replace("'#87617b'","'#87617b','#a6a35c','#7a9daf','#b78069','#8e9bba'")
s=s.replace('五条学习主线，一张清晰的书桌。',"${data.tracks.length} 条学习主线，一张清晰的书桌。")
s=s.replace("'${data.tracks.length} 条学习主线，一张清晰的书桌。找到章节，写下答案，留下自己的理解。'","`${data.tracks.length} 条学习主线，一张清晰的书桌。找到章节，写下答案，留下自己的理解。`")
s=s.replace(" $('#count').textContent=items.length;"," $('#track-count').textContent=data.tracks.length;\n $('#count').textContent=items.length;")
start=s.index("if(e.href&&t.reader)");end=s.index("$('#show-guide').onclick",start)
s=s[:start]+"$('#detail-actions').append(link('阅读本章教材',e.reading));$('#scope').textContent=e.scope;$('#chapter-files').replaceChildren(...e.files.map(f=>{const b=document.createElement('button');b.textContent=f.label;b.onclick=()=>doc(f.path);return b}));"+s[end:]
s=s.replace("async function doc(path){","let docRequest=0;async function doc(path){const request=++docRequest;$('#doc-links').replaceChildren();")
s=s.replace("$('#doc').textContent=await r.text()","const text=await r.text();if(request!==docRequest)return;$('#doc').textContent=text;const base=new URL('/'+path,location.origin);for(const match of text.matchAll(/\\[([^\\]]+)\\]\\(([^)]+)\\)/g)){try{const u=new URL(match[2],base);if(u.origin!==location.origin)continue;const a=document.createElement('a');a.textContent=match[1]+' ↗';a.href=u.href;a.target='_blank';$('#doc-links').append(a)}catch{}}")
s=s.replace(" list();\n}"," const current=items.find(e=>state(e.id)['状态']==='学习中')||items.find(e=>state(e.id)['状态']==='未开始');$('#resume').hidden=!current;if(current){const h=document.createElement('h2');h.textContent=state(current.id)['状态']==='学习中'?'继续学习':'建议下一步';const p=document.createElement('p');p.textContent=current.title+' · '+current.kind;const b=document.createElement('button');b.textContent='进入学习';b.onclick=()=>open(current);$('#resume').replaceChildren(h,p,b)}\n list();\n}")
s += "\nconst theme=localStorage.getItem('study-theme')||'dark';document.body.dataset.theme=theme;$('#theme').textContent=theme==='dark'?'切换浅色':'切换深色';$('#theme').onclick=()=>{const next=document.body.dataset.theme==='dark'?'light':'dark';document.body.dataset.theme=next;localStorage.setItem('study-theme',next);$('#theme').textContent=next==='dark'?'切换浅色':'切换深色'};\n"
p.write_text(s,encoding='utf-8')
p=R/'workbench/style.css';s=p.read_text(encoding='utf-8');s+='''
/* 九主线本地工作台：深色运维面板，保留浅色阅读选项。 */
:focus-visible{outline:2px solid #67b8c7}body[data-theme=dark]{--ink:#e0e7ef;--muted:#a3b1bf;--paper:#10151c;--line:#334050;--accent:#dca27c;color-scheme:dark}body[data-theme=dark] aside{background:#151e29;color:#dce7f1}body[data-theme=dark] nav button{color:#c7d3df}body[data-theme=dark] nav button.active,body[data-theme=dark] nav button:hover{background:#2b3d50;border-color:#6386a6}body[data-theme=dark] .book,body[data-theme=dark] button,body[data-theme=dark] input,body[data-theme=dark] select,body[data-theme=dark] textarea,body[data-theme=dark] pre,body[data-theme=dark] .actions a{background:#19232e;color:var(--ink);border-color:var(--line)}body[data-theme=dark] button:hover{background:#26384a;border-color:#8aa5c0}body[data-theme=dark] .book{--book-color:#a9c3d4!important}body[data-theme=dark] .primary{background:#3f6981;color:#fff}body[data-theme=dark] #toast{background:#d4e4f2;color:#17232e}.stamp{display:none}.brand{font-family:'Microsoft YaHei',sans-serif;font-size:28px}h1{font-family:'Microsoft YaHei',sans-serif;font-size:30px}nav{margin-top:25px;overflow-y:auto}#chapter-files{margin-top:15px}#doc-links{margin-bottom:15px}header{gap:12px}header>a{margin-left:auto}header button{font-size:12px;padding:7px 10px}.book{min-height:185px}#resume{margin:0 0 25px}#resume p{margin:10px 0}.status.complete{color:#65b98b}
@media(max-width:650px){nav{overflow-x:auto;overflow-y:hidden}.brand span{font-size:10px}header{flex-wrap:wrap;height:auto;min-height:65px;padding:10px 0}header>a{margin-left:0}header button{margin-left:auto}}
''';p.write_text(s,encoding='utf-8')
