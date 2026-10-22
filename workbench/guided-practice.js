/* 题目与实际作答并排；右侧只读预览磁盘上的真实文件，运行与检查复用既有工具。 */
window.GuidedPractice=(()=>{
 'use strict';
 const $=id=>document.getElementById(id),node=(tag,text)=>{const e=document.createElement(tag);if(text!==undefined)e.textContent=text;return e;};
 let current=null,revision=0,regions=[],regionIndex=0,button,code,info,title,panel,layout,question,refresh,jump,run,check,result,last,busy=false,fileChoice,fileLabel,selectedPath=null,pageEpoch=0,help,footer,modeButton,hidden;
 const LABELS={
  unfinished:['还没开始写','warn','按上面指出的位置写出实现，再点“检查本题”。'],
  'compile-error':['编译没有通过','bad','代码没能编译成功，所以一组样例都没有运行。按上面的报错改。'],
  failed:['样例没有全部通过','bad','对照每组输入、期望与实际输出找差异。'],
  passed:['登记样例全部通过','good','这是固定样例的结果，不等于所有情况都正确，也不会自动记为完成。'],
  manual:['本题没有自动判分','muted','按本题 README 的完成标准逐项人工自检。'],
  unregistered:['本题还没接入统一检查','muted','按本题说明操作；不要把它当成已通过。'],
  error:['检查没有完成','bad',''],
  ran:['已运行，不判题','info','这一步只运行程序。要核对答案请点“检查本题”。'],
  timeout:['运行超时','bad','程序可能进入死循环，或在等待输入。请检查循环条件和输入。']
 };
 function view(show){
  $('detail').classList.toggle('code-focus',show);button?.setAttribute('aria-pressed',String(show));
  if(show)for(const id of ['show-guide','show-answer'])$(id).setAttribute('aria-pressed','false');
  if(show&&panel){panel.scrollIntoView({block:'start'});code.focus({preventScroll:true});}
 }
 function init(){
  if(layout)return;
  layout=node('div');layout.id='exercise-layout';question=node('section');question.id='exercise-question';question.setAttribute('aria-label','题目与要求');
  const tabs=document.querySelector('.doc-tabs');tabs.before(layout);question.append(tabs,$('doc'),$('check-explanation'));
  panel=node('section');panel.id='exercise-code';panel.setAttribute('aria-label','当前作答代码');
  const header=node('div');header.className='code-panel-header';title=node('h3','本题代码框架');header.append(title,node('span','只读预览'));
  fileLabel=node('label','查看本题文件：');fileLabel.className='code-file-choice';fileChoice=node('select');fileChoice.id='exercise-file';fileChoice.setAttribute('aria-label','选择本题代码文件');fileChoice.onchange=()=>{selectedPath=fileChoice.value;load();};fileLabel.append(fileChoice);
  help=node('p','这是磁盘上的真实作答文件。在 VS Code 改完并保存，再回到这里点“检查本题”。');help.className='code-panel-help';
  const controls=node('div');controls.className='code-panel-controls';
  jump=node('button','定位补全区');jump.type='button';jump.onclick=()=>locate(true);
  refresh=node('button','刷新代码');refresh.type='button';refresh.onclick=()=>load();
  run=node('button','运行本题');run.type='button';run.onclick=()=>execute('run');
  check=node('button','检查本题');check.type='button';check.className='primary';check.onclick=()=>execute('check');
  hidden=node('button','再测没见过的输入');hidden.type='button';hidden.id='exercise-hidden';hidden.onclick=()=>runHidden();
  modeButton=node('button','切换');modeButton.type='button';modeButton.id='exercise-mode';modeButton.onclick=()=>toggleMode();
  controls.append(jump,refresh,run,check,hidden,modeButton);
  info=node('p');info.id='code-preview-status';info.setAttribute('role','status');info.setAttribute('aria-live','polite');
  code=node('div');code.className='guided-code-lines';code.tabIndex=0;code.setAttribute('role','region');code.setAttribute('aria-label','当前文件代码，只读；可滚动查看');
  result=node('div');result.id='exercise-result';result.setAttribute('role','status');result.setAttribute('aria-live','polite');result.hidden=true;
  last=node('p');last.id='exercise-last';last.hidden=true;
  footer=node('p','“运行”只看程序输出；“检查”才比对登记样例。两者都不会替你记完成。');footer.className='code-panel-help';
  panel.append(header,help,fileLabel,controls,info,last,code,result,footer);layout.append(question,panel);
  button=node('button','看代码框架');button.id='show-code';button.type='button';button.setAttribute('aria-pressed','false');button.onclick=()=>view(true);tabs.append(button);
  for(const id of ['show-guide','show-answer'])$(id).addEventListener('click',()=>view(false));
 }
 function locate(next=false){
  if(!regions.length)return;
  if(next)regionIndex=(regionIndex+1)%regions.length;
  const target=regions[regionIndex];code.scrollTop=Math.max(0,target.getBoundingClientRect().top-code.getBoundingClientRect().top+code.scrollTop-60);
  info.textContent='当前补全区：'+target.dataset.region+'。高亮部分与实际文件一致。';
 }
 async function load(){
  if(!current)return;const own=++revision,e=current,path=selectedPath||e.work;refresh.disabled=true;jump.disabled=true;regions=[];regionIndex=0;code.replaceChildren();info.textContent='正在读取本题的实际作答文件…';
  const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),7000);
  try{
   const r=await fetch('/'+path,{signal:controller.signal,cache:'no-store'});if(!r.ok)throw Error('读取失败（'+r.status+'）');const text=await r.text();if(own!==revision)return;
   title.textContent='本题代码 · '+path.split('/').pop();
   const lines=text.replace(/\r\n/g,'\n').split('\n');let start=0;
   const end=lines.findIndex(s=>s.includes('【本题说明结束】'));if(end>=0){start=end+1;while(start<lines.length&&/^\s*(?:\/\/)?\s*$/.test(lines[start]))start++;}
   // 「从零写」的题只有题头、后面还没有任何代码：把题头留着显示，
   // 否则右侧只剩几个空行号，看不出这是个还没写的文件。
   // 判断标准是“说明结束后没有任何真正的代码行”，只有注释也算还没写。
   if(end>=0&&lines.slice(end+1).every(l=>!l.trim()||/^\s*\/\//.test(l)))start=0;
   let active=false;
   for(let i=start;i<lines.length;i++){
    const s=lines[i],begin=s.match(/^\s*\/\*\s*BEGIN\s+(\d+)(.*?)\*\//i),finish=/^\s*\/\*\s*END\s+\d+\s*\*\//i.test(s);
    if(begin)active=true;
    const row=node('div');row.className='guided-code-line'+(active?' fill-region':'');const number=node('span',String(i+1));number.className='code-line-number';number.setAttribute('aria-hidden','true');const source=node('code',s||' ');row.append(number,source);
    if(begin){row.classList.add('fill-start');row.dataset.region=begin[1]+begin[2].replace(/^\s*[:：]?\s*/,' · ');regions.push(row);}
    code.append(row);if(finish)active=false;
   }
   const blankOnly=end>=0&&start===0;
   jump.hidden=!regions.length;
   info.textContent=regions.length?'已读取实际文件，共'+regions.length+'个补全区。'
    :(blankOnly?'本题从零写：文件里只有题头说明，写完把题头替换成你自己的代码。'
              :'已读取实际文件；本题没有补全区，按题目要求完成整份实现。');
   if(regions.length)requestAnimationFrame(()=>{if(own===revision)locate();});
  }catch(err){if(own===revision)info.textContent='代码暂未读取成功，请点“刷新代码”重试。'+(err.name==='AbortError'?'连接超时。':err.message);}
  finally{clearTimeout(timer);if(own===revision)refresh.disabled=false;}
 }
 function lastLine(){
  try{
   const raw=localStorage.getItem('gp-last:'+current.work);if(!raw)return '';
   const d=JSON.parse(raw);const label=(LABELS[d.state]||['结果未知'])[0];
   const minutes=Math.max(1,Math.round((Date.now()-d.at)/60000));
   const when=minutes<60?minutes+' 分钟前':Math.round(minutes/60)+' 小时前';
   const count=d.samples?'（'+d.samples.passed+'/'+d.samples.total+' 组）':'';
   return '上次检查：'+label+count+' · '+when+'。这只是上次的结果，现在要重新点“检查本题”。';
  }catch{return ''}
 }
 let mode='guided';
 async function loadMode(){
  if(!current?.work){modeButton.hidden=true;return;}
  try{
   const r=await fetch('/api/exercise/mode',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({work:current.work})});
   const d=await r.json();
   if(d.error)throw Error(d.error);
   mode=d.mode||'guided';
   if(d.hasTemplate===false){modeButton.hidden=true;return;}
  }catch{modeButton.hidden=true;return;}
  modeButton.hidden=false;
  modeButton.textContent=mode==='blank'?'从零写 · 要骨架':'引导版 · 试从零写';
  modeButton.title=mode==='blank'?'这道题现在是空的，全部自己写。点一下拿回骨架（会先备份）。':'这道题给了骨架。点一下清空成从零写（会先备份）。';
 }
 async function toggleMode(){
  if(!current?.work||busy)return;
  const next=mode==='blank'?'guided':'blank';
  const ask=next==='blank'?'会清空这道题的 work.cpp（原内容备份到 模板/），换成从零写。继续？':'会把骨架写回来，覆盖你当前这个文件（原内容备份到 模板/）。继续？';
  if(!window.confirm(ask))return;
  busy=true;modeButton.disabled=true;
  try{
   const r=await fetch('/api/exercise/mode',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({work:current.work,mode:next})});
   const d=await r.json();
   if(d.error)throw Error(d.error);
   mode=d.mode||next;
   result.hidden=true;info.textContent='';last.hidden=true;
   await loadMode();load();
  }catch(e){window.alert('切换失败：'+e.message);}
  finally{busy=false;modeButton.disabled=false;}
 }
 async function runHidden(){
  if(!current?.work||busy)return;
  busy=true;hidden.disabled=true;result.hidden=false;result.className='exercise-result running';
  result.replaceChildren(node('p','正在用参考实现现算几组没登记的输入…'));
  try{
   const r=await fetch('/api/exercise/hidden',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({work:selectedPath||current.work})});
   const d=await r.json();
   if(d.error)throw Error(d.error);
   const tone=d.state==='agree'?'good':(d.state==='differ'?'bad':'warn');
   const title={agree:'隐藏样例全部一致',differ:'隐藏样例有分歧',unsupported:'这题不支持隐藏样例',unfinished:'还没开始写',
     'compile-error':'先让程序编译通过','timeout':'超时'}[d.state]||'结果未知';
   result.className='exercise-result '+tone;result.replaceChildren();
   const head=node('p');head.className='result-head';head.append(node('strong',title));result.append(head);
   const pre=node('pre',d.log||'');pre.className='result-output';pre.tabIndex=0;result.append(pre);
   result.scrollIntoView({block:'nearest'});
  }catch(e){result.className='exercise-result bad';result.replaceChildren(node('p','检查失败：'+e.message));}
  finally{busy=false;hidden.disabled=false;}
 }
 function render(d,entry){
  const [label,tone,hint]=LABELS[d.state]||['结果未知','muted',''];
  result.hidden=false;result.className='exercise-result '+tone;result.replaceChildren();
  const head=node('p');head.className='result-head';head.append(node('strong',label));
  if(d.samples)head.append(node('span','　'+d.samples.passed+'/'+d.samples.total+' 组样例通过'));
  result.append(head);
  if(d.detail)result.append(node('p',d.detail));
  if(hint&&hint!==d.detail)result.append(node('p',hint));
  const text=[d.stderr,d.stdout].filter(t=>t&&t.trim()).join('\n').trim();
  if(text){const pre=node('pre',text);pre.className='result-output';pre.tabIndex=0;pre.setAttribute('aria-label','运行与检查输出，可滚动');result.append(pre);}
  // 通过后只给一个“由你确认”的入口，不自动打勾。
  if(d.state==='passed'&&entry?.id){
   const bar=node('p');bar.className='result-done';
   bar.append(node('span','要记为已完成吗？这不影响上面的检查结果：'));
   const mark=node('button','标为已完成');mark.type='button';
   mark.onclick=()=>{
    window.dispatchEvent(new CustomEvent('study-mark-done',{detail:{id:entry.id}}));
    mark.disabled=true;mark.textContent='已提交，请核对学习记录';
   };
   bar.append(mark);result.append(bar);
  }
  if(entry?.work){
   try{localStorage.setItem('gp-last:'+entry.work,JSON.stringify({state:d.state,samples:d.samples,at:Date.now()}))}catch{}
   last.hidden=true;
  }
 }
 async function execute(action){
  if(!current?.work||busy)return;
  const ownPage=pageEpoch,entry=current;
  // 判分对象是“当前选中的作答文件”：同一道题有补写版和从零写版，
  // 下拉选了哪份就判哪份；头文件不能单独跑。
  const target=selectedPath||entry.work;
  if(!/\.(cpp|c|sh)$/i.test(target)){
   result.hidden=false;result.className='exercise-result warn';
   result.replaceChildren(node('p','这是头文件，不能单独编译。请在文件下拉里选择 work.cpp（补写版）或 from-scratch.cpp（从零写）。'));
   return;
  }
  busy=true;run.disabled=check.disabled=true;
  result.hidden=false;result.className='exercise-result running';
  result.replaceChildren(node('p',action==='check'?'正在编译并核对登记样例…':'正在编译并运行…'));
  try{
   const r=await fetch('/api/exercise/'+action,{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({work:target})});
   let d={};try{d=await r.json()}catch{}
   if(ownPage!==pageEpoch)return;
   if(!r.ok)throw Error(d.error||('请求失败（'+r.status+'）'));
   render(d,entry);
   // 结果区在代码下面，宽屏时可能不在视野内；出现后滚一下，不用自己找。
   result.scrollIntoView({block:'nearest',behavior:'smooth'});
   if(action==='check')load();
  }catch(e){
   if(ownPage!==pageEpoch)return;
   result.className='exercise-result bad';
   result.replaceChildren(node('p','没能完成：'+e.message),node('p','可以刷新页面重试，或按本题说明在 VS Code 里运行“本题：检查作答”。'));
  }finally{if(ownPage===pageEpoch){busy=false;run.disabled=check.disabled=false;}}
 }
 function show(e){
  init();pageEpoch++;current=e;busy=false;if(modeButton)loadMode();run.disabled=check.disabled=false;
  const remote=Boolean(window.StudyAccess?.remote);
  help.textContent=remote?'这里预览电脑上的真实作答。运行和检查在电脑上执行，结果回到这里——和坐在电脑前点是一样的。':'这是磁盘上的真实作答文件。在 VS Code 改完并保存，再回到这里点“检查本题”。';
  footer.textContent=remote?'改完保存，直接点“检查本题”；结果只属于这一题，切题后旧结果不会串过来。':'“运行”只看程序输出；“检查”才比对登记样例。两者都不会替你记完成。';
  const files=e.work_files?.length?e.work_files:[{path:e.work,label:'我的作答',editable:true}];
  selectedPath=files[0]?.path;fileChoice.replaceChildren();for(const f of files){const o=node('option',f.label);o.value=f.path;fileChoice.append(o);}fileLabel.hidden=files.length<2;
  const enabled=Boolean(e.work&&/\.(?:cpp|c|sh)$/.test(e.work));$('detail').classList.toggle('has-code',enabled);panel.hidden=!enabled;button.hidden=!enabled;view(false);
  result.hidden=true;result.replaceChildren();
  last.hidden=true;
  // 旧的只读源码按钮与右侧实际文件重复，这里收起。
  for(const b of $('chapter-files').querySelectorAll('button'))if(b.textContent==='查看我的作答（只读）')b.hidden=enabled;
  if(!enabled){revision++;code.replaceChildren();return;}
  const previous=current?.work?lastLine():'';
  if(previous){last.textContent=previous;last.hidden=false;}
  title.textContent='本题代码 · '+e.work.split('/').pop();load();
 }
 return{show};
})();
