const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');const path=require('path');
const BASE='http://127.0.0.1:18765';
const out=path.join(__dirname,'verification');
(async()=>{
fs.mkdirSync(out,{recursive:true});
const browser=await chromium.launch({headless:true,channel:'msedge'});
const page=await browser.newPage({viewport:{width:1440,height:900}});
const errors=[];page.on('pageerror',e=>errors.push(e.message));
const fails=[];const check=(ok,label)=>{if(!ok)fails.push(label);console.log((ok?'PASS ':'FAIL ')+label)};

await page.goto(BASE+'/workbench/original.html#page=206');
await page.waitForFunction(()=>{const i=document.getElementById('or-img');return i&&i.complete&&i.naturalWidth>0});
check((await page.inputValue('#or-page'))==='206','深链接 #page=206 生效');
check((await page.textContent('#or-panel-title')).includes('印刷页 191'),'面板标题显示印刷页 191');
check((await page.textContent('#or-badges')).includes('已校对原文'),'状态标签：已校对原文');
check((await page.textContent('#or-cap')).includes('原页影像'),'图注标明原页影像');

await page.click('#or-tab-text');
await page.waitForFunction(()=>document.querySelector('#or-text h2,#or-text h3,#or-text h4'));
const text=await page.textContent('#or-text');
check(text.includes('6.3 有理数'),'已校对原文含 6.3 标题');
check(text.includes('int main() {'),'已校对原文含示例代码块');
check((await page.locator('#or-text figure img').count())===2,'原文层两处运行截图转为图片');
await page.screenshot({path:path.join(out,'original-text.png'),fullPage:false});

await page.click('#or-tab-image');
await page.click('#or-next');
await page.waitForFunction(()=>document.getElementById('or-page').value==='207');
check((await page.textContent('#or-badges')).includes('已校对原文'),'翻到 207 仍是已校对页');

// 全书 659 页已全部识别（2026-10-21 完成），不再存在「未识别页」样本。
// 原断言用 300 页当未识别页，已随全量识别失效，改为校验该页同样能读原文。
await page.fill('#or-page','300');await page.press('#or-page','Enter');
await page.waitForFunction(()=>document.getElementById('or-page').value==='300');
check((await page.textContent('#or-badges')).includes('已校对原文'),'全量识别后 300 页也是已校对页');
await page.click('#or-tab-text');await page.waitForTimeout(300);
check(!(await page.textContent('#or-status')).includes('尚未识别'),'已识别页不出现「尚未识别」提示');

await page.fill('#or-page','206');await page.press('#or-page','Enter');
await page.waitForFunction(()=>document.getElementById('or-page').value==='206');
await page.screenshot({path:path.join(out,'original-desktop.png')});

const links=await page.$$eval('#or-links a',as=>as.map(a=>a.getAttribute('href')));
check(links.some(h=>h==='/#task=ROB-L06'),'旁侧含本题深链接 /#task=ROB-L06');
check(links.some(h=>(decodeURIComponent(h).includes('我的作答/main.cpp'))),'旁侧含自己的作答入口');
for(const href of links.filter(h=>!h.startsWith('books/'))){
  const full=href.startsWith('http')?href:BASE+encodeURI(href);
  const res=await page.request.get(full);
  check(res.ok()||res.status()===304,'链接可达 '+href);
}

await page.setViewportSize({width:1024,height:768});
await page.waitForTimeout(200);
await page.screenshot({path:path.join(out,'original-tablet.png')});
check(!(await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth)),'平板宽度无横向溢出');

await page.setViewportSize({width:390,height:844});
await page.waitForTimeout(200);
await page.screenshot({path:path.join(out,'original-mobile.png')});
check(!(await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth)),'手机宽度无横向溢出');

await page.setViewportSize({width:1440,height:900});
await page.click('#or-theme');
check((await page.evaluate(()=>document.documentElement.dataset.theme))==='dark','深色主题切换');
await page.screenshot({path:path.join(out,'original-dark.png')});
await page.click('#or-theme');

await page.goto(BASE+'/#task=ROB-L06');
await page.waitForSelector('#detail[open]');
check((await page.textContent('#detail-title')).includes('类'),'原任务深链接仍可用');
check((await page.locator('#detail-actions a').allTextContents()).some(text=>text.includes('阅读本章教材')),'原有“阅读本章教材”入口保留');
await page.keyboard.press('Escape');

check(errors.length===0,'无前端脚本报错 '+(errors.join(' | ')||''));
await browser.close();
console.log(fails.length?('FAILURES: '+fails.join(' ; ')):'ALL PASS');
process.exit(fails.length?1:0)})().catch(e=>{console.error('ERROR',e.message);process.exit(2)});
