const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs'),path=require('path');
const BASE='http://127.0.0.1:18765';
const out='D:/工作区/工作区/learning-update/cpp-continuous-reading/界面验收';
(async()=>{
 fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({channel:'msedge',headless:true,args:['--no-proxy-server']});
 try {
 const page=await browser.newPage({viewport:{width:1440,height:1000}}),fails=[],errors=[];
 page.on('pageerror',e=>errors.push(e.message));
 const check=(v,label)=>{console.log((v?'PASS ':'FAIL ')+label);if(!v)fails.push(label)};
 async function open(n,hash=''){
  await page.goto(BASE+'/workbench/chapter.html?chapter='+n+hash);
  await page.waitForFunction(()=>document.querySelectorAll('#ch-content .ch-page-marker').length>0);
 }
 const m=await (await page.request.get(BASE+'/api/original/manifest')).json();
 for(let c=1;c<=20;c++){
  const file='cpp/主教材/章节学习/第'+String(c).padStart(2,'0')+'章/原书阅读.md';
  const res=await page.request.get(BASE+'/'+file),text=await res.text();
  const start=m.chapter_links[c].chapter_page,end=c<20?m.chapter_links[c+1].chapter_page-1:638;
  const pages=[...text.matchAll(/###### \[原页 · PDF (\d+)\]/g)].map(x=>Number(x[1]));
  check(res.ok()&&pages.length===end-start+1&&pages.every((p,i)=>p===start+i),'第'+c+'章页序完整 '+start+'—'+end);
 }
 await open(2);
 check(await page.locator('#ch-select option').count()===20,'20章选择入口');
 check((await page.textContent('#ch-title')).includes('函数与库'),'第2章标题');
 check(await page.locator('#ch-toc a').count()>3,'本章目录');
 check((await page.textContent('#ch-content')).includes('double f(double x)'),'代码内容可读');
 check((await page.getAttribute('#ch-guide','href')).includes('README.md'),'练习入口指向章节说明');
 check((await page.getAttribute('#ch-practice','href'))==='/#task=ROB-L02','开始练习指向题目');
 check(!(await page.textContent('#ch-content')).includes('.meta.json'),'正文无后台元数据');
 // 所有章节图示链接在磁盘验收；这里检查真实渲染图片。
 await page.locator('#ch-content figure img').first().scrollIntoViewIfNeeded();
 await page.waitForFunction(()=>{const img=document.querySelector('#ch-content figure img');return img?.complete&&img.naturalWidth>0});
 check(true,'章节插图实际加载');
 await page.evaluate(()=>scrollTo(0,0));
 await page.screenshot({path:path.join(out,'章节阅读-电脑.png')});
 await page.selectOption('#ch-font','21');
 check(await page.evaluate(()=>getComputedStyle(document.querySelector('#ch-content')).fontSize)==='21px','字号切换');
 await page.selectOption('#ch-font','17');
 await page.locator('#ch-toc a').nth(2).click();
 check(page.url().includes('#section-'),'目录跳转到本页小节');
 await open(2,'#page=70');
 await page.waitForTimeout(400);
 check((await page.textContent('#ch-status')).includes('PDF 70 /'),'原页深链接定位');
 await page.reload();await page.waitForSelector('#ch-resume:not([hidden])');
 check((await page.textContent('#ch-resume')).includes('70'),'刷新后可恢复阅读位置');
 await open(2);await page.reload();await page.waitForSelector('#ch-resume:not([hidden])');
 check((await page.textContent('#ch-resume')).includes('70'),'只打开章首不覆盖上次阅读位置');
 await page.click('#ch-resume');await page.waitForTimeout(400);
 check((await page.textContent('#ch-status')).includes('PDF 70 /'),'恢复按钮回到上次页');
 await open(16);
 check((await page.textContent('#ch-range')).includes('478—508'),'第16章从478页开始');
 await open(20);check(await page.locator('#ch-next').isHidden(),'最后一章无无效下一章');
 await open(1);check(await page.locator('#ch-prev').isHidden(),'第一章无无效上一章');
 for(const [w,h,label] of [[1024,768,'平板横屏'],[820,1180,'平板竖屏'],[390,844,'手机']]){
  await page.setViewportSize({width:w,height:h});await open(2);
  check(!await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth),label+'无页面横向溢出');
  if(w<=1000){check(!await page.locator('#ch-directory').getAttribute('open'),label+'目录默认收起');await page.click('#ch-directory>summary');await page.locator('#ch-toc a').first().click();check(!await page.locator('#ch-directory').getAttribute('open'),label+'选小节后收起目录');}
  await page.evaluate(()=>scrollTo(0,0));await page.screenshot({path:path.join(out,'章节阅读-'+label+'.png')});
 }
 await page.setViewportSize({width:1440,height:1000});await open(2);await page.click('#ch-theme');
 check(await page.evaluate(()=>document.documentElement.dataset.theme)==='dark','深色主题');
 await page.screenshot({path:path.join(out,'章节阅读-深色.png')});
 const catalog=await(await page.request.get(BASE+'/api/catalog')).json();
 const cpp=catalog.items.filter(e=>e.chapter_guide);
 check(cpp.length>=100&&cpp.every(e=>e.original.startsWith('workbench/chapter.html?chapter=')),'主教材任务统一进入连续阅读');
 await page.goto(BASE+'/workbench/help.html?doc='+encodeURIComponent('cpp/主教材/章节学习/README.md'));
 await page.waitForSelector('#help-doc table');
 check(await page.locator('#help-doc a[href="/workbench/chapter.html?chapter=2"]').count()===1,'章节索引原文链接进入专用阅读器');
 await page.goto(BASE+'/workbench/help.html?doc='+encodeURIComponent('cpp/主教材/章节学习/第02章/README.md'));
 await page.waitForSelector('#help-doc h1');
 check(await page.locator('#help-doc a[href="/workbench/chapter.html?chapter=2"]').count()===1,'章节说明原文链接进入专用阅读器');
 await page.goto(BASE+'/#task=ROB-L02');await page.waitForSelector('#detail[open]');
 check((await page.getAttribute('#detail-actions a:has-text("阅读本章教材")','href')).includes('chapter.html?chapter=2'),'工作台阅读按钮已接入');
 check(errors.length===0,'无脚本报错 '+errors.join('|'));
 fs.writeFileSync(path.join(out,'结果.json'),JSON.stringify({fails,errors,checks:'20章页序、原图、目录、阅读恢复、练习链接、桌面平板手机、深色、工作台集成'},null,2));
 if(fails.length)throw Error(fails.join(';'));
 } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1});
