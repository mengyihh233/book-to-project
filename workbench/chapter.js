/* 章节阅读只读；阅读位置留在本浏览器，不写学习完成进度。 */
(() => {
 'use strict';
 const $=id=>document.getElementById(id);
 const number=new URLSearchParams(location.search).get('chapter')||'1';
 const chapter=/^(?:[1-9]|1\d|20)$/.test(number)?Number(number):1;
 const key='cpp-reading-page-'+chapter;
 const path='cpp/主教材/章节学习/第'+String(chapter).padStart(2,'0')+'章/原书阅读.md';
 const get=(key)=>{try{return localStorage.getItem(key)}catch{return null}};
 const set=(key,value)=>{try{localStorage.setItem(key,value)}catch{}};
 const chapterURL=c=>'/workbench/chapter.html?chapter='+c;
 const doc=p=>'/workbench/help.html?doc='+encodeURIComponent(p);
 let markers=[],first=0,last=0;
 function jump(id) { const target=document.getElementById(id);if(target){target.scrollIntoView();target.focus({preventScroll:true});} }
 function images(article) {
  for(const a of article.querySelectorAll('a')) {
   if(!a.textContent.startsWith('查看图示：'))continue;
   const u=new URL(a.href);
   if(u.origin!==location.origin||!/^\/cpp\/roberts\/original\/figures\/\d{4}\.fig-[a-z0-9-]+\.png$/.test(u.pathname))continue;
   const figure=document.createElement('figure'),img=document.createElement('img'),cap=document.createElement('figcaption');
   img.src=u.href;img.alt=a.textContent.slice(5);img.loading='lazy';cap.textContent=img.alt;
   figure.append(img,cap);
   const parent=a.parentElement;
   if(parent.tagName==='P'&&parent.textContent.trim()===a.textContent.trim())parent.replaceWith(figure);else a.replaceWith(figure);
  }
 }
 function position(save=true) {
  let current=first;
  for(const marker of markers){if(marker.getBoundingClientRect().top>140)break;current=Number(marker.dataset.page);}
  if(save)set(key,String(current));
  $('ch-status').textContent='正在读 PDF '+current+' / 本章 '+first+'—'+last+' 页 · 阅读位置仅记在当前浏览器';
 }
 async function start() {
  $('ch-theme').textContent=document.documentElement.dataset.theme==='dark'?'切换浅色':'切换深色';
  $('ch-theme').onclick=()=>{const theme=document.documentElement.dataset.theme==='dark'?'light':'dark';document.documentElement.dataset.theme=theme;set('study-theme',theme);$('ch-theme').textContent=theme==='dark'?'切换浅色':'切换深色'};
  const font=get('cpp-reading-font');if(['17','19','21'].includes(font))$('ch-font').value=font;
  const applyFont=()=>{document.body.style.setProperty('--reading-size',$('ch-font').value+'px');set('cpp-reading-font',$('ch-font').value)};
  applyFont();$('ch-font').onchange=applyFont;
  $('ch-directory').open=matchMedia('(min-width:1001px)').matches;
  try {
   const response=await fetch('/api/original/manifest');if(!response.ok)throw Error('章节目录读取失败');
   const manifest=await response.json(),links=manifest.chapter_links;
   const info=links?.[String(chapter)];if(!info)throw Error('本章索引尚未发布');
   const main=info.main;
   for(let n=1;n<=20;n++){
    const option=document.createElement('option');option.value=String(n);option.textContent=links[String(n)].title;$('ch-select').append(option);
   }
   $('ch-select').value=String(chapter);$('ch-select').onchange=()=>location.assign(chapterURL($('ch-select').value));
   for(const [id,c] of [['ch-prev',chapter-1],['ch-next',chapter+1]]){
    if(c<1||c>20){$(id).hidden=true;}else $(id).href=chapterURL(c);
   }
   first=Number(info.chapter_page);last=chapter<20?Number(links[String(chapter+1)].chapter_page)-1:638;
   $('ch-title').textContent=info.title;document.title=info.title+' · 连续读原书';
   $('ch-range').textContent='PDF '+first+'—'+last+' 页 · 正文、复习与原书习题';
   const count=(manifest.pages||[]).filter(p=>p.pdf_page>=first&&p.pdf_page<=last).reduce((s,p)=>s+(p.open_questions||0),0);
   $('ch-note').textContent='按已校对页稿汇编，原文疑点仍保留。本章登记待核对项 '+count+' 处，详情可从相应原页查看；“已校对”不代表没有识别误差。';
   const guide='cpp/主教材/章节学习/第'+String(chapter).padStart(2,'0')+'章/README.md';
   $('ch-end-guide').href='/workbench/course.html?track=cpp&chapter='+chapter;document.querySelector('.ch-header>a').href='/workbench/course.html?track=cpp&chapter='+chapter;document.querySelector('.ch-header>a').textContent='← 返回第'+chapter+'章';
   // 读完这章，页尾要能直接去下一章，不用滚回顶部。
   if(chapter<20)$('ch-end-next').href=chapterURL(chapter+1);else $('ch-end-next').hidden=true;
   $('ch-practice').href=main.deep_link||'/#task='+encodeURIComponent(main.id);
   $('ch-practice').target='_blank';$('ch-practice').rel='noopener';
   $('ch-pdf').href='/books/cpp-roberts.pdf#page='+first;
   $('ch-local').href=doc('guide/C++连续阅读与练习使用说明.md');
   const source=await fetch('/'+path);if(!source.ok)throw Error('本章连续阅读稿尚未发布，请先从原版PDF阅读');
   const markdown=await source.text(),start=markdown.indexOf('###### [原页');
   if(start<0||!BookReader.render($('ch-content'),markdown.slice(start),path))throw Error('阅读稿格式异常，请打开原版PDF');
   images($('ch-content'));
   let seq=0;
   for(const h of $('ch-content').querySelectorAll('h2,h3,h4,h5,h6')){
    const m=h.tagName==='H6'&&h.textContent.match(/^原页 · PDF (\d+)$/);
    if(m){h.id='page-'+m[1];h.dataset.page=m[1];h.classList.add('ch-page-marker');markers.push(h);}
    else {h.id='section-'+seq++;if(['H2','H3'].includes(h.tagName)){
     const a=document.createElement('a');a.textContent=h.textContent;a.href='#'+h.id;
     a.onclick=()=>{if(innerWidth<=1000)$('ch-directory').open=false;};$('ch-toc').append(a);
    }}
    h.tabIndex=-1;
   }
   const saved=Number(get(key));
   if(saved>first&&saved<=last){$('ch-resume').hidden=false;$('ch-resume').textContent='继续上次：PDF '+saved+' 页';$('ch-resume').onclick=()=>jump('page-'+saved);}
   const explicit=location.hash.match(/^#(?:page=(\d+)|(section-\d+))$/);
   if(explicit)jump(explicit[1]?'page-'+explicit[1]:explicit[2]);
   position(Boolean(explicit));
   let timer;addEventListener('scroll',()=>{clearTimeout(timer);timer=setTimeout(position,180)},{passive:true});
   addEventListener('hashchange',()=>{const m=location.hash.match(/^#(?:page=(\d+)|(section-\d+))$/);if(m)jump(m[1]?'page-'+m[1]:m[2]);});
  } catch(error) { $('ch-status').textContent=error.message+'。可从“原版 PDF”或工作台返回教材。'; }
 }
 start();
})();
