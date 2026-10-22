(()=>{'use strict';
 const $=s=>document.querySelector(s);let text='',path='',raw=false,request=0;
 const allowed=v=>window.BookReader?.isReadable(v)===true;
 function jump(hash){let id;try{id=decodeURIComponent(hash.replace(/^#/,''))}catch{return}const el=document.getElementById(id);if(el&&$('#help-doc').contains(el)){el.scrollIntoView({block:'start'});el.tabIndex=-1;el.focus({preventScroll:true});}}
 function theme(){const dark=document.documentElement.dataset.theme==='dark';document.body.dataset.theme=dark?'dark':'light';$('#help-theme').textContent=dark?'切换暖白':'切换深色'}
 theme();$('#help-theme').onclick=()=>{const next=document.documentElement.dataset.theme==='dark'?'light':'dark';document.documentElement.dataset.theme=next;try{localStorage.setItem('study-theme',next)}catch{}theme()};
 try{const size=localStorage.getItem('study-reading-size-v1');if(['17','19','21'].includes(size))$('#help-font').value=size}catch{}
 const font=()=>{document.body.style.setProperty('--doc-size',$('#help-font').value+'px');try{localStorage.setItem('study-reading-size-v1',$('#help-font').value)}catch{}};font();$('#help-font').onchange=font;
 function display(){const target=$('#help-doc'),rendered=!raw&&window.BookReader?.render(target,text,path);if(!rendered){const pre=document.createElement('pre');pre.className='source-view';pre.textContent=text;target.replaceChildren(pre)}
  $('#help-source').disabled=!window.marked?.lexer;$('#help-source').textContent=!window.marked?.lexer?'原文显示（阅读组件不可用）':raw?'切换阅读排版':'查看原文';$('#help-source').setAttribute('aria-pressed',String(raw||!rendered));
  const toc=$('#help-toc');toc.replaceChildren();const headings=rendered?[...target.querySelectorAll('h2,h3')]:[];$('#help-outline').hidden=!headings.length;$('#help-outline').open=false;
  for(const h of headings){const a=document.createElement('a');a.textContent=h.textContent;a.href='#'+encodeURIComponent(h.id);a.className=h.tagName==='H3'?'toc-sub':'';a.onclick=ev=>{ev.preventDefault();history.replaceState(null,'',location.pathname+location.search+a.hash);jump(a.hash);if(innerWidth<=1000)$('#help-outline').open=false;};toc.append(a)}
 }
 async function load(value,{replace=false,anchor=''}={}){const token=++request;path=value;raw=false;text='';$('#help-source').disabled=true;$('#help-doc').textContent='';$('#help-outline').hidden=true;$('#help-status').textContent='正在读取资料…';$('#help-original').removeAttribute('href');
  if(!allowed(value)){$('#help-status').textContent='这个地址不是支持的本区Markdown资料。请从上方选择资料，或返回工作台。';return}
  $('#help-original').href='/'+value;
  if(![...$('#guide-select').options].some(o=>o.value===value)){const o=document.createElement('option');o.value=value;o.textContent=value.split('/').pop();$('#guide-select').append(o)}$('#guide-select').value=value;
  const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),8000);
  try{const r=await fetch('/'+value,{signal:controller.signal});if(!r.ok)throw Error('资料读取失败（'+r.status+'）');const body=await r.text();if(token!==request)return;if(!body.trim()){$('#help-status').textContent='这份资料暂时没有内容，可选择其他资料。';return}text=body;history[replace||new URLSearchParams(location.search).get('doc')===value?'replaceState':'pushState'](null,'','?doc='+encodeURIComponent(value)+anchor);display();const h=$('#help-doc h1');$('#help-status').textContent='正在阅读：'+(h?h.textContent:value.split('/').pop())+' · 可按目录跳转，代码单独复制';document.title=(h?h.textContent:'使用说明')+' · 书桌';if(anchor)jump(anchor);else window.scrollTo(0,0)}catch(e){if(token!==request)return;$('#help-status').textContent=(e.name==='AbortError'?'读取超时':e.message)+'。可点“重新读取”，或返回工作台。'}finally{clearTimeout(timer)}
 }
 $('#help-source').onclick=()=>{raw=!raw;display()};$('#help-retry').onclick=()=>load(path,{replace:true,anchor:location.hash});$('#guide-select').onchange=()=>load($('#guide-select').value);
 $('#help-doc').onclick=event=>{const a=event.target.closest('a');if(!a||event.ctrlKey||event.metaKey||event.shiftKey||event.altKey||event.button>0)return;try{const u=new URL(a.href);const rel=u.pathname==='/workbench/help.html'?u.searchParams.get('doc'):decodeURIComponent(u.pathname).replace(/^\//,'');if(u.origin===location.origin&&allowed(rel)){event.preventDefault();if(rel===path&&u.hash){history.replaceState(null,'',location.pathname+location.search+u.hash);jump(u.hash)}else load(rel,{anchor:u.hash});}}catch{}};
 const initial=new URLSearchParams(location.search).get('doc')||'guide/平板联动快速上手.md';load(initial,{replace:true,anchor:location.hash});window.addEventListener('popstate',()=>load(new URLSearchParams(location.search).get('doc')||'guide/平板联动快速上手.md',{replace:true,anchor:location.hash}));
})();

