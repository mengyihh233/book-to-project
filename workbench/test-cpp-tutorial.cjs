const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');
const BASE='http://127.0.0.1:18765',OUT='D:/工作区/工作区/learning-update/cpp-quickcourse/界面验收';
(async()=>{
 fs.mkdirSync(OUT,{recursive:true});const browser=await chromium.launch({headless:true,channel:'msedge',args:['--no-proxy-server']});
 const errors=[],fails=[],checks=[];let progressPosts=0;
 const check=(ok,label)=>{checks.push(label);console.log((ok?'PASS ':'FAIL ')+label);if(!ok)fails.push(label);};
 try {
 const page=await browser.newPage({viewport:{width:1440,height:1000}});
 page.on('pageerror',e=>errors.push(e.message));page.on('request',r=>{if(r.method()==='POST'&&r.url().includes('/api/progress'))progressPosts++;});
 const data=await(await page.request.get(BASE+'/workbench/cpp-lessons.json')).json();
 await page.goto(BASE+'/workbench/cpp-tutorial.html');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='程序、输出与换行');
 check(await page.locator('#lesson-menu a').count()===data.lessons.filter(e=>e.level==='core').length,'基础目录数量');
 check(await page.locator('#output-details').getAttribute('open')===null,'先预测，示例输出默认收起');
 await page.click('#quiz-check');check((await page.textContent('#quiz-feedback')).includes('先选'),'未选择时给出提示');
 await page.check('input[name="lesson-answer"][value="1"]');await page.click('#quiz-check');
 check((await page.textContent('#quiz-feedback')).includes('还不对'),'错误回答解释入口');
 check((await page.textContent('#lesson-progress')).includes('0 / '+data.lessons.length),'回答错误不记完成');
 await page.check('input[name="lesson-answer"][value="0"]');await page.click('#quiz-check');
 check((await page.textContent('#quiz-feedback')).includes('答对'),'正确回答即时反馈');
 check((await page.textContent('#lesson-progress')).includes('0 / '+data.lessons.length),'答对也不自动替用户记完成');
 await page.click('#lesson-done');check((await page.textContent('#lesson-progress')).includes('1 / '+data.lessons.length),'显式记录本机已练');
 await page.click('#lesson-done');check((await page.textContent('#lesson-progress')).includes('0 / '+data.lessons.length),'可撤销已练记录');
 await page.click('#edit-tab');await page.fill('#lesson-editor','// local draft\n#include <iostream>\nint main() { std::cout << "mine"; }');
 await page.click('#lesson-next');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='表达式、语句与代码块');
 await page.click('#lesson-prev');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='程序、输出与换行');await page.click('#edit-tab');
 check((await page.inputValue('#lesson-editor')).includes('local draft'),'切换小课保留代码草稿');
 check((await page.textContent('#example-code'))===data.lessons[0].code,'代码草稿不改原示例');
 await page.reload();await page.waitForSelector('#lesson-menu a');await page.click('#edit-tab');check((await page.inputValue('#lesson-editor')).includes('local draft'),'刷新保留代码草稿');
 await page.click('#example-tab');await page.screenshot({path:OUT+'/短讲即练-电脑.png'});
 await page.fill('#lesson-search','函数');check(await page.locator('#lesson-menu a').count()>=1&&await page.locator('#lesson-menu a').count()<data.lessons.length,'按知识点搜索');
 await page.fill('#lesson-search','no-match-xyz');check((await page.textContent('#lesson-menu')).includes('没有匹配'),'无结果提示');await page.fill('#lesson-search','');
 for(const e of data.lessons){
  await page.evaluate(id=>location.hash='lesson='+id,e.id);await page.waitForFunction(t=>document.querySelector('#lesson-title').textContent===t,e.title);
  check((await page.textContent('#example-code'))===e.code,'示例对应 '+e.id);
  await page.check('input[name="lesson-answer"][value="'+e.quiz.answer+'"]');await page.click('#quiz-check');
  if(!(await page.textContent('#quiz-feedback')).includes('答对'))fails.push('题目答案 '+e.id);
 }
 await page.goto(BASE+'/workbench/cpp-tutorial.html');await page.waitForFunction(t=>document.querySelector('#lesson-title').textContent===t,data.lessons.at(-1).title);
 check(true,'无hash入口继续上次小课');
 await page.goto(BASE+'/workbench/cpp-tutorial.html#lesson=functions');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='函数、返回值与作用域');
 for(const [w,h,name] of [[1024,768,'平板横屏'],[820,1180,'平板竖屏'],[390,844,'手机']]){
  await page.setViewportSize({width:w,height:h});await page.reload();await page.waitForSelector('#lesson-menu a',{state:'attached'});
  check(!await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth),name+'无横向溢出');
  if(w<=1000){check(await page.getAttribute('#lesson-directory','open')===null,name+'目录收起');await page.click('#lesson-directory>summary');await page.locator('#lesson-menu a').first().click();check(await page.getAttribute('#lesson-directory','open')===null,name+'选课自动收起目录');}
  await page.screenshot({path:OUT+'/短讲即练-'+name+'.png'});
 }
 await page.click('#lesson-theme');check(await page.evaluate(()=>document.documentElement.dataset.theme)==='dark','深色主题');
 await page.screenshot({path:OUT+'/短讲即练-深色.png'});
 await page.goto(BASE);await page.waitForSelector('.book');await page.locator('#nav button').filter({hasText:'C++ 程序设计'}).click();
 check(await page.locator('#track-actions>a[href="/workbench/cpp-tutorial.html"]').isVisible(),'工作台C++主入口可见');
 check(progressPosts===0,'未改教材共享学习进度');check(errors.length===0,'无脚本错误 '+errors.join('|'));
 fs.writeFileSync(OUT+'/结果.json',JSON.stringify({checks,fails,errors,progressPosts},null,2));if(fails.length)throw Error(fails.join(';'));
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1});

