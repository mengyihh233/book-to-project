(() => {
 'use strict';
 const $=id=>document.getElementById(id),KEY='cpp-quickcourse-v1';
 const node=(tag,text)=>{const e=document.createElement(tag);if(text!==undefined)e.textContent=text;return e;};
 const read=key=>{try{return JSON.parse(localStorage.getItem(key))}catch{return null}};
 const write=(key,value)=>{try{localStorage.setItem(key,JSON.stringify(value));return true}catch{return false}};
 let data,current,index=0,edited=false;
 const savedState=read(KEY);
 const state=savedState&&typeof savedState==='object'&&!Array.isArray(savedState)?savedState:{};
 if(!Array.isArray(state.done))state.done=[];
 function route(){return data.lessons.filter(e=>$('lesson-scope').value==='all'||e.level!=='supplement');}
 const href=id=>'#lesson='+encodeURIComponent(id);
 const doc=p=>'/workbench/help.html?doc='+encodeURIComponent(p);
 function progress(){
  state.done=state.done.filter(id=>data.lessons.some(l=>l.id===id));
  $('lesson-progress').textContent='本机已记录 '+state.done.length+' / '+data.lessons.length+' 节';
  $('lesson-done').textContent=state.done.includes(current.id)?'已记为练过 · 点击取消':'记为本节已练';
  $('lesson-done').setAttribute('aria-pressed',String(state.done.includes(current.id)));
 }
 function menu(){
  const filter=$('lesson-search').value.trim().toLowerCase(),box=$('lesson-menu');box.replaceChildren();
  for(let g=1;g<=data.groups.length;g++){
   const found=route().filter(e=>e.group===g&&(!filter||(e.title+' '+data.groups[g-1]+' '+(e.terms||[]).join(' ')).toLowerCase().includes(filter)));
   if(!found.length)continue;box.append(node('h2',g+' · '+data.groups[g-1]));
   for(const lesson of found){const a=node('a',(state.done.includes(lesson.id)?'✓ ':'')+lesson.title+(lesson.level==='supplement'?' · 按需':''));a.href=href(lesson.id);a.setAttribute('aria-current',String(lesson.id===current.id));a.onclick=()=>{if(innerWidth<=1000)$('lesson-directory').open=false;};box.append(a);}
  }
  if(!box.children.length)box.append(node('p','没有匹配的小课，试试“函数”或清除搜索。'));
 }
 function mode(edit){edited=edit;$('edit-area').hidden=!edit;$('example-view').hidden=edit;$('example-tab').setAttribute('aria-pressed',String(!edit));$('edit-tab').setAttribute('aria-pressed',String(edit));}
 function link(label,url){const a=node('a',label);a.href=url;a.target='_blank';a.rel='noopener';return a;}
 function practice(){
  const box=$('practice-actions');box.replaceChildren();
  if(!StudyAccess.remote){const b=node('button','在电脑 VS Code 打开学习区');b.onclick=async()=>{try{const r=await fetch('/api/open',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({mode:'code',path:'workspaces/cpp.code-workspace'})});if(!r.ok)throw Error();$('lesson-status').textContent='已发送工作区打开请求；请在下方所示作答文件中练习。';}catch{$('lesson-status').textContent='打开失败，可手动打开workspaces/cpp.code-workspace。';}};box.append(b);}
  box.append(StudyAccess.editorAction(current.practice.path.split('/').slice(0,-1).join('/')));
  box.append(link('只读查看自己的文件','/'+current.practice.path),link('关联练习说明',doc(current.practice.guide)));
  const refresh=node('button','刷新网页作答连接');refresh.onclick=async()=>{refresh.disabled=true;await StudyAccess.load();practice();};box.append(refresh);
 }
 function show(){
  const id=new URLSearchParams(location.hash.slice(1)).get('lesson')||state.last;
  current=data.lessons.find(e=>e.id===id)||data.lessons[0];
  if(current.level==='supplement')$('lesson-scope').value='all';
  const visible=route();index=visible.findIndex(e=>e.id===current.id);
  document.title=current.title+' · C++语法小课';$('lesson-title').textContent=current.title;
  $('lesson-position').textContent=($('lesson-scope').value==='core'?'基础先学':'全部小课')+' · 第 '+(index+1)+' / '+visible.length+' 节 · '+data.groups[current.group-1]+' · 约 '+current.minutes+' 分钟';
  const source=current.book_source;$('lesson-book-source').replaceChildren();if(source){$('lesson-book-source').append(document.createTextNode('原书联系：'),link(source.title,'/workbench/chapter.html?chapter='+source.chapter+(source.pdf_page?'#page='+source.pdf_page:'')),document.createTextNode(' · '+source.note));}
  $('lesson-explain').replaceChildren(...current.explain.map(p=>node('p',p)));
  $('pitfall-card').hidden=!current.pitfall;$('pitfall-card').open=false;
  $('lesson-pitfall').textContent=current.pitfall||'';
  const steps=current.practice.steps||[];
  $('practice-steps-card').hidden=!steps.length;$('practice-steps-card').open=false;
  $('practice-steps').replaceChildren(...steps.map(s=>node('li',s)));
  const model=(data.practice_models||[]).find(m=>m.id===current.practice.model);
  $('practice-model-card').hidden=!model;$('practice-model-card').open=false;
  $('practice-model-title').textContent=model?model.title:'';
  $('practice-model-note').textContent=model?model.note:'';
  $('practice-model-code').textContent=model?model.code:'';
  $('practice-model-output').textContent=model?model.output:'';
  $('example-code').textContent=current.code;$('example-output').textContent=current.output;
  const syntax=current.syntax||[];
  $('syntax-card').hidden=!syntax.length;
  $('lesson-syntax').replaceChildren(...syntax.map(item=>{const row=node('div');row.append(node('dt',item.form),node('dd',item.meaning));return row;}));
  const lines=current.lines||[];
  $('lines-card').hidden=!lines.length;
  $('lesson-lines').replaceChildren(...lines.map(text=>node('li',text)));
  const saved=read(KEY+':code:'+current.id);$('lesson-editor').value=typeof saved==='string'?saved:current.code;
  $('lesson-status').textContent=typeof saved==='string'?'本节有已恢复的本机代码草稿，可点“改代码”继续。':'先预测示例，再展开输出或做小测。';
  mode(false);$('run-area').hidden=true;$('run-output').textContent='';$('output-details').open=false;$('quiz-answer').open=false;$('quiz-feedback').textContent='';delete $('quiz-feedback').dataset.correct;
  $('quiz-prompt').textContent=current.quiz.prompt;$('quiz-options').replaceChildren();
  for(const [i,text]of current.quiz.options.entries()){
   const label=node('label'),radio=node('input');radio.type='radio';radio.name='lesson-answer';radio.value=String(i);label.append(radio,document.createTextNode(text));$('quiz-options').append(label);
  }
  $('quiz-hint').textContent='提示：'+current.hint;$('quiz-reason').textContent='解释：'+current.quiz.reason;
  if(current.group<=2)$('quiz-reason').append(document.createTextNode(' '),link('本组实操参考与预期结果',doc('cpp/语法小课/提示与答案/README.md')));
  $('practice-instruction').textContent=current.practice.instruction;$('practice-path').textContent='你的文件：'+current.practice.path;
  practice();progress();menu();
  for(const [name,n]of [['lesson-prev',index-1],['lesson-next',index+1]]){const a=$(name);a.hidden=n<0||n>=visible.length;if(!a.hidden)a.href=href(visible[n].id);}
  QuickPractice.show(current);state.last=current.id;state.scope=$('lesson-scope').value;write(KEY,state);window.scrollTo(0,0);
 }
 $('example-tab').onclick=()=>mode(false);$('edit-tab').onclick=()=>mode(true);
 $('lesson-editor').oninput=()=>{$('lesson-status').textContent=write(KEY+':code:'+current.id,$('lesson-editor').value)?'代码草稿已在当前浏览器暂存；实际结果请到VS Code编译确认。':'浏览器无法暂存，请复制代码及时保存。';};
 async function runSnippet(){
  const code=edited?$('lesson-editor').value:current.code;
  const area=$('run-area'),status=$('run-status'),out=$('run-output'),button=$('run-example');
  area.hidden=false;out.textContent='';status.textContent='正在本机编译并运行…';button.disabled=true;
  try{
   const response=await fetch('/api/run-snippet',{method:'POST',headers:{'Content-Type':'application/json'},
    body:JSON.stringify({code,stdin:(current.practice&&current.practice.stdin)||''})});
   const data=await response.json();
   if(data.error){status.textContent='没能运行：'+data.error;return;}
   const ms=data.ms||0;
   if(data.stage==='compile'){status.textContent='编译没过（'+ms+' ms）：按下面的报错改代码。';out.textContent=data.stderr||'';return;}
   if(data.stage==='timeout'){status.textContent='运行超时（上限 3 秒）。';out.textContent=data.stderr||'';return;}
   status.textContent='运行完成 · 退出码 '+data.exitCode+' · 用时 '+ms+' ms'+(data.exitCode===0?'':'（程序异常结束）');
   out.textContent=(data.stdout||'(没有输出)')+(data.stderr?'\n[stderr]\n'+data.stderr:'');
  }catch(error){status.textContent='请求失败：'+error.message+'。检查工作台服务是否在运行。';}
  finally{button.disabled=false;}
 }
 $('run-example').onclick=runSnippet;
 $('lesson-editor').addEventListener('keydown',event=>{if((event.ctrlKey||event.metaKey)&&event.key==='Enter'){event.preventDefault();runSnippet();}});
 $('copy-example').onclick=async()=>{try{await navigator.clipboard.writeText(edited?$('lesson-editor').value:current.code);$('lesson-status').textContent='已复制当前代码；粘贴到自己的文件后实际编译运行。';}catch{$('lesson-status').textContent='剪贴板不可用，请长按或手动选择代码复制。';}};
 $('quiz-check').onclick=()=>{const selected=document.querySelector('input[name="lesson-answer"]:checked');if(!selected){$('quiz-feedback').textContent='先选一个答案，再检查。';return;}const ok=Number(selected.value)===current.quiz.answer;$('quiz-feedback').dataset.correct=String(ok);$('quiz-feedback').textContent=ok?'答对了。'+current.quiz.reason:'还不对，再对照示例想一想；可展开提示与解释。';};
 $('lesson-done').onclick=()=>{state.done=state.done.includes(current.id)?state.done.filter(x=>x!==current.id):[...state.done,current.id];const ok=write(KEY,state);progress();menu();if(!ok)$('lesson-status').textContent='当前浏览器无法保存小课记录。';};
 $('lesson-search').oninput=menu;
 $('lesson-scope').onchange=()=>{state.scope=$('lesson-scope').value;write(KEY,state);if(!route().some(e=>e.id===current.id))location.hash=href(route()[0].id);else show();};
 function concepts(){
  $('book-essentials').replaceChildren(...(data.core_summary||[]).map(s=>node('li',s)));
  const render=()=>{const q=$('concept-search').value.trim();const entries=(data.concepts||[]).filter(c=>!q||(c.term+c.definition).includes(q));$('concept-list').replaceChildren(...entries.map(c=>{const box=node('div');box.className='concept-entry';const a=node('a',c.term);a.href=href(c.lesson);a.onclick=()=>{$('concept-desk').open=false;};box.append(a,node('p',c.definition));return box;}));if(!entries.length)$('concept-list').append(node('p','没有匹配的概念，可清空搜索。'));};$('concept-search').oninput=render;render();
 }
 $('lesson-theme').onclick=()=>{const dark=document.documentElement.dataset.theme==='dark';document.documentElement.dataset.theme=dark?'light':'dark';$('lesson-theme').textContent=dark?'切换深色':'切换浅色';try{localStorage.setItem('study-theme',dark?'light':'dark')}catch{}};
 const wideLayout=matchMedia('(min-width:1001px)');
 $('lesson-directory').open=wideLayout.matches;
 wideLayout.addEventListener('change',e=>{ $('lesson-directory').open=e.matches; });
 async function start(){try{
  const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),6000);
  let response;try{response=await fetch('/workbench/cpp-lessons.json',{signal:controller.signal});}finally{clearTimeout(timer);}
  if(!response.ok)throw Error('课程读取失败');data=await response.json();
  if(!Array.isArray(data.lessons)||!data.lessons.length||data.lessons.length>200||new Set(data.lessons.map(e=>e.id)).size!==data.lessons.length)throw Error('课程索引异常');
  $('lesson-scope').value=state.scope==='all'?'all':'core';concepts();
  const last=state.last;
  if(last&&data.lessons.some(e=>e.id===last)){$('lesson-resume').hidden=false;$('lesson-resume').onclick=()=>{location.hash=href(last);};}
  $('lesson-theme').textContent=document.documentElement.dataset.theme==='dark'?'切换浅色':'切换深色';
  show();addEventListener('hashchange',show);StudyAccess.load().then(practice);
 }catch(error){QuickPractice.failed();$('lesson-status').textContent=(error.name==='AbortError'?'课程读取超时，请重新读取':error.message)+'；可返回工作台或从文件库打开cpp/语法小课/README.md。';}}
 start();
})();

