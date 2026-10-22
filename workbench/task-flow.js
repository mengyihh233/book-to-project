window.TaskFlow=(()=>{
 'use strict';let current=null,back='/workbench/directory.html';const $=id=>document.getElementById(id),n=(tag,text)=>{const e=document.createElement(tag);e.textContent=text;return e},link=(text,url)=>{const e=n('a',text);e.href=url;return e};
 function leave(){window.DeskEase?.stash();location.href=back;}
 function show(e){
  current=e;document.body.classList.add('task-view');const names={cpp:'C++学习',opencv:'机器视觉学习',math:'高等数学学习',linux:'Linux学习'},track=names[e.track]?e.track:null;
  const group=track?'/workbench/course.html?track='+track:'/workbench/directory.html';let match=e.id.match(/^(?:ROB-L|roberts-ch|opencv-L|linux-L)(\d+)/);back=group+(track==='cpp'&&match?'&chapter='+Number(match[1]):'');
  const b=$('task-breadcrumb');b.replaceChildren(link('学习首页','/workbench/directory.html'),n('span','›'),link(names[e.track]||'学习目录',group));if(match)b.append(n('span','›'),link('第'+Number(match[1])+'章',back));b.append(n('span','›'),n('span',/^ROB-L/.test(e.id)?'章内综合练习':e.kind==='原书习题'?'本题':'当前练习'));
  $('close').textContent=track==='cpp'&&match?'← 返回本章':'← 返回学科';
  $('close').setAttribute('aria-label',$('close').textContent);
  const actions=$('detail-actions'),more=document.createElement('details'),summary=n('summary','教材、预览与文件位置'),holder=document.createElement('div');more.className='desk-extra';holder.className='actions';
  for(const child of [...actions.children]){
   if(child.matches('button')&&['打开本题作答','在 VS Code 作答','在网页 VS Code 作答'].some(t=>child.textContent.startsWith(t)))continue;
   if(child.matches('a')&&child.textContent.startsWith('在网页 VS Code 作答'))continue;
   if(child.tagName==='DETAILS'){for(const item of [...child.querySelector('.actions')?.children||[]])holder.append(item);child.remove();}
   else holder.append(child);
  }
  holder.append($('doc-location'));if(holder.childNodes.length){more.append(summary,holder);$('chapter-files').before(more);}
  $('doc').after($('check-explanation'));
  $('chapter-files').after($('coach-panel'));
  const box=$('check-explanation');box.replaceChildren(n('p','① 保存 → “本题：运行作答”观察程序　② “本题：检查作答”核对规则'));
  if(e.track==='math'&&!e.work)box.replaceChildren(n('p','在本专题work.md或extra-work.md对应题目下写解答；原书题与附加题分开。'));
  box.append(n('p',e.check==='book'?'本题自动比较已登记的输入输出样例；检查的是自己的作答。':e.check==='svg'?'本题由同一检查入口自动选择图形专项。':e.check==='manual'?'本题没有独立自动评分，按题目要求自检。':e.track==='math'?'数学文字题在对应题目下写解答，对照解析人工核对。':'本题尚未接入统一检查入口，请按本题说明操作。'));
  if(e.work)box.append(n('p','写在这里：'+e.work.split('/').slice(-2).join('/')));
  if(/^ROB-L/.test(e.id))$('detail-title').textContent=e.title+' · 章内综合练习';
  // 同一章的上一题/下一题，看完直接翻，不用回章节页。
  const old=$('task-pager');if(old)old.remove();
  if(e.prev||e.next){
   const pager=document.createElement('nav');pager.id='task-pager';pager.className='task-pager';pager.setAttribute('aria-label','同一章的上一题与下一题');
   const jump=id=>{const a=n('a',id===e.prev?'← 上一题':'下一题 →');a.href='#task='+encodeURIComponent(id);return a};
   if(e.prev)pager.append(jump(e.prev));
   if(e.next)pager.append(jump(e.next));
   $('chapter-files').after(pager);
  }
  window.GuidedPractice?.show(e);
 }
 document.addEventListener('DOMContentLoaded',()=>{
  $('detail').addEventListener('cancel',event=>{if(current){event.preventDefault();leave();}});
  document.querySelector('.brand')?.addEventListener('click',event=>{event.preventDefault();location.href='/workbench/directory.html';});
 });
 return{show,leave,active:()=>Boolean(current)};
})();
