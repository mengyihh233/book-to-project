/* 展示层：复用任务与文件，不生成新题、不自动保存学习进度。 */
window.DeskEase=(()=>{
 const $=id=>document.getElementById(id);
 const CONTEXT='study-desk-context-v1',DRAFT='study-desk-draft-v1:';
 const read=key=>{try{return JSON.parse(localStorage.getItem(key))}catch{return null}};
 const write=(key,value)=>{try{if(value===null)localStorage.removeItem(key);else localStorage.setItem(key,JSON.stringify(value));return true}catch{return false}};
 const names={'README.md':'题目与作答要求','solution.md':'做完再看：解析','reference.cpp':'参考代码（C++）','reference.c':'参考代码（C）','reference.sh':'参考脚本','notes.md':'我的笔记','answers.md':'我的文字作答','work.cpp':'我的作答（C++）','work.c':'我的作答（C）','work.sh':'我的作答（Shell）','work.md':'我的文字作答','extra-work.md':'附加题作答','main.cpp':'程序入口','input.txt':'手动测试输入','CMakeLists.txt':'CMake构建配置','原书阅读.md':'连续读原书'};
 const cv=['概览','OpenCV入门','基本数据类型','图像与大型数组','数组操作','绘图与标注','函数对象','图像、视频与数据文件','跨平台窗口','滤波与卷积','图像变换','图像分析','直方图与模板','轮廓','背景减除','关键点与描述子','跟踪','相机模型与标定','投影与三维视觉','机器学习基础','StatModel学习模型','目标检测','OpenCV展望'];
 let ready=false,current=null,baseline=null;const expanded=new Set();
 function restore(data){
  ready=true;const context=read(CONTEXT);
  if(location.hash.includes('task='))return null;
  if(!context||typeof context!=='object'||!['',...data.tracks.map(t=>t.id)].includes(context.track))return null;
  for(const id of ['search','kind','status','scope','cpp-book']){
   const value=context[id],el=$(id);if(typeof value!=='string')continue;
   if(el.tagName==='INPUT'||[...el.options].some(o=>o.value===value))el.value=value;
  }
  return context;
 }
 function remember(track){
  $('scope').closest('label').hidden=Boolean(track);
  $('cpp-book').closest('label').hidden=Boolean(track&&track!=='cpp');
  const tools=$('track-actions');
  if(track&&!tools.querySelector('.desk-extra')){
   const details=document.createElement('details');details.className='desk-extra';const summary=document.createElement('summary');summary.textContent='环境、笔记与其他入口';
   const holder=document.createElement('div');holder.className='actions';
   for(const node of [...tools.children])if(!['视觉实验','语法小课','按章节学习','本区使用指引','中文目录与工作区','原版教材','在 VS Code 打开','在 WSL Ubuntu 学习','在网页 VS Code 作答'].some(s=>node.textContent.startsWith(s)))holder.append(node);
   if(holder.children.length){details.append(summary,holder);tools.append(details);}
  }
  if(!ready)return;
  const value={track};for(const id of ['search','kind','status','scope','cpp-book','chapter-filter'])value[id]=$(id).value;
  write(CONTEXT,value);
 }
 function chapters(items,track,choose,chapterKey){
  remember(track);
  const wrap=$('chapter-browser'),grid=$('chapter-cards');
  wrap.hidden=!['cpp','opencv','linux'].includes(track)||!items.length;
  grid.replaceChildren();if(wrap.hidden)return;
  const groups=new Map();
  for(const item of items){if(item.role==='参考教材')continue;const key=chapterKey(item);if(!/^ch\d+$/.test(key))continue;if(!groups.has(key))groups.set(key,[]);groups.get(key).push(item);}
  let index=0;
  for(const [key,group] of [...groups].sort((a,b)=>a[0].localeCompare(b[0]))){
   const n=Number(key.slice(2)),main=group.find(e=>e.id===('ROB-L'+String(n).padStart(2,'0'))||e.id===track+'-L'+String(n).padStart(2,'0'))||group[0];
   const card=document.createElement('div');card.className='chapter-card';card.hidden=index++>=6&&!expanded.has(track);
   const h=document.createElement('h3');h.textContent=track==='opencv'?'第'+n+'章 · '+cv[n-1]:main.title;
   const p=document.createElement('p');p.textContent=group.length+' 项现有任务 · '+(track==='cpp'&&n>5?'章内练习已配，课后题尚未逐题整理':'说明、作答与参考解析');
   const actions=document.createElement('div');actions.className='chapter-card-actions';
   const a=document.createElement('a');a.textContent='进入本章';a.href='/workbench/course.html?track='+track+'&chapter='+n;a.target='_blank';a.rel='noopener';
   const b=document.createElement('button');b.textContent='找本章练习';b.onclick=()=>{choose(key);$('practice-list').scrollIntoView({block:'start'});};actions.append(a);card.append(h,p,actions);grid.append(card);
  }
  wrap.hidden=!grid.children.length;
  wrap.querySelector('.chapter-more')?.remove();
  if(groups.size>6){const more=document.createElement('button');more.className='chapter-more';more.textContent=expanded.has(track)?'收起后续章节':'展开全部 '+groups.size+' 章';more.setAttribute('aria-expanded',String(expanded.has(track)));more.onclick=()=>{expanded.has(track)?expanded.delete(track):expanded.add(track);chapters(items,track,choose,chapterKey)};wrap.append(more);}
 }
 function files(e,show){
  const box=$('chapter-files');box.replaceChildren();
  const actions=$('detail-actions'),extra=document.createElement('details');extra.className='desk-extra';
  const summary=document.createElement('summary');summary.textContent='目录、原版PDF与预览';const holder=document.createElement('div');holder.className='actions';
  for(const node of [...actions.children])if(!['打开本题作答','在 VS Code 作答','在网页 VS Code 作答','阅读本章教材','本章讲解与全部练习'].some(s=>node.textContent.startsWith(s)))holder.append(node);
  if(holder.children.length){extra.append(summary,holder);actions.append(extra);}
  const make=f=>{const b=document.createElement('button');const name=f.path.split('/').pop();b.textContent=names[name]||name;b.title=f.path;b.onclick=()=>{if(name==='原书阅读.md')window.open(BookReader.documentUrl(f.path),'_blank','noopener');else show(f.path);};return b};
  const other=document.createElement('details');other.className='task-materials';const sum=document.createElement('summary');sum.textContent='补充资料与文件';const body=document.createElement('div');body.className='actions';other.append(sum,body);
  const refs=document.createElement('details');refs.className='task-materials';const rs=document.createElement('summary');rs.textContent='参考代码（先独立作答）';const rb=document.createElement('div');rb.className='actions';refs.append(rs,rb);
  if(e.work){const b=make({path:e.work});b.textContent='查看我的作答（只读）';box.append(b);}
  for(const f of e.files){
   if(f.path===e.guide||f.path===e.answer||f.path===e.work)continue;
   if(/^reference\./.test(f.label)||f.path===e.source){rb.append(make(f));continue;}
   body.append(make(f));
  }
  if(body.children.length)box.append(other);if(rb.children.length)box.append(refs);
  $('task-work-location').textContent=e.work?'作答文件：'+e.work:'作答位置以本题说明为准。';
 }
 function stash(){
  if(!current||!baseline)return;
  const note=$('note').value,status=$('edit-status').value;
  const changed=note!==baseline.note||status!==baseline.status;
  const ok=write(DRAFT+current.id,changed?{note,status,revision:baseline.revision}:null);
  $('draft-status').textContent=changed?(ok?'本机草稿已暂存；点“保存学习记录”才会同步到学习区。':'尚未保存；当前浏览器无法暂存草稿，请及时保存。'):'学习记录已保存；更改后需再次保存。';
 }
 function enter(task,record){
  current=task;baseline={note:record['复盘']||'',status:record['状态'],revision:record._revision};
  const draft=read(DRAFT+task.id);
  if(draft&&typeof draft.note==='string'&&['未开始','学习中','已完成'].includes(draft.status)){
   $('note').value=draft.note;$('edit-status').value=draft.status;
   $('draft-status').textContent=draft.revision===baseline.revision?'已恢复本机未保存草稿；检查后点“保存学习记录”。':'已恢复本机草稿；共享记录曾更新，请核对后再保存。';
  }else $('draft-status').textContent='更改只会留作本机草稿，点“保存学习记录”才会同步。';
 }
 function saved(record){if(!current)return;baseline={note:$('note').value,status:$('edit-status').value,revision:record?._revision};write(DRAFT+current.id,null);$('draft-status').textContent='已保存到学习区，另一设备刷新共享进度后可见。';}
 $('note').addEventListener('input',stash);$('edit-status').addEventListener('change',stash);
 $('detail').addEventListener('close',()=>{stash();if(location.hash.includes('task='))history.replaceState(null,'',location.pathname+location.search);});
 addEventListener('pagehide',stash);
 return{restore,remember,chapters,files,stash,enter,saved};
})();

