(()=>{'use strict';
 const $=id=>document.getElementById(id),node=(tag,text)=>{const el=document.createElement(tag);if(text!==undefined)el.textContent=text;return el},doc=p=>'/workbench/help.html?doc='+encodeURIComponent(p);
 function link(text,path){const a=node('a',text);a.href=path;return a;}
 const topics={cpp:'按教材章节学习；语法小课用于按需补基础。',opencv:'中文导读 → 章节练习 → 查看图像和处理结果。',math:'微分方程、极坐标、极限与下册内容，按现有路线学习。',network:'一条请求走完全程：浏览器、协议栈、交换机、路由器、运营商、服务器。',linux:'在Ubuntu终端练命令、Shell和CMake，源码继续共用D盘。'};
 function openButton(text,path,mode){const b=node('button',text);b.onclick=async()=>{b.disabled=true;try{const r=await fetch('/api/open',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({path,mode})});if(!r.ok)throw Error();$('directory-status').textContent='已发送打开请求，请查看电脑上的窗口。';}catch{$('directory-status').textContent='打开未成功。电脑上可双击 D:/Book-Learning/'+path+'；平板请使用网页VS Code入口。';}finally{b.disabled=false}};return b;}
 function card(t){const box=node('article');box.className='directory-card';box.dataset.track=t.id;box.append(node('h3',t.name),node('p',topics[t.id]||'先读本区指引，按章节选择内容。'));
  const actions=node('div');actions.className='actions';actions.append(link('进入'+t.name,['cpp','opencv','math','linux','network'].includes(t.id)?'/workbench/course.html?track='+t.id:doc(t.guide)));box.append(actions);
  const details=node('details'),summary=node('summary','在电脑或平板写代码'),buttons=node('div');buttons.className='actions';buttons.append(StudyAccess.editorAction(t.id));if(!StudyAccess.remote){buttons.append(openButton('电脑 VS Code',t.workspace,'code'));if(['cpp','linux'].includes(t.id))buttons.append(openButton('Ubuntu VS Code','workspaces/focus-wsl.code-workspace','wsl'));}details.append(summary,buttons);box.append(details);return box;
 }
 async function load(){const retry=$('directory-retry');retry.hidden=true;const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),6000);try{const r=await fetch('/workbench/folders.json',{signal:controller.signal});if(!r.ok)throw Error();const data=await r.json();await StudyAccess.load();for(const id of ['focus-directories','linux-directory','other-directory-list'])$(id).replaceChildren();for(const t of data.tracks)$(t.focus?'focus-directories':t.id==='linux'?'linux-directory':'other-directory-list').append(card(t));$('directory-status').textContent='';}catch{$('directory-status').textContent='目录暂时读取失败；可重试，或从电脑上的“学习区使用说明.md”进入。';retry.hidden=false;}finally{clearTimeout(timer)}}
 $('directory-retry').onclick=load;load();
})();

