const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');const BASE='http://127.0.0.1:18765',OUT='D:/工作区/工作区/learning-update/cpp-practice-polish/界面验收';
(async()=>{
 fs.mkdirSync(OUT,{recursive:true});const browser=await chromium.launch({channel:'msedge',headless:true,args:['--no-proxy-server']});const errors=[],checks=[];
 const check=(ok,label)=>{if(!ok)throw Error(label);checks.push(label);console.log('PASS '+label)};
 try{
 const page=await browser.newPage({viewport:{width:1440,height:1000}});page.on('pageerror',e=>errors.push(e.message));
 const data=await(await page.request.get(BASE+'/workbench/cpp-lessons.json')).json();
 async function go(id){await page.goto(BASE+'/workbench/cpp-tutorial.html#lesson='+id);await page.waitForFunction(()=>document.querySelectorAll('#lesson-menu a').length>0&&!document.querySelector('#fill-check').disabled);}
 await go('output');await page.click('#fill-check');check((await page.textContent('#fill-feedback')).includes('先填'),'空输入提示');
 await page.fill('#fill-answer','c o u t');await page.click('#fill-check');check(await page.getAttribute('#fill-feedback','data-correct')==='false','不把关键词内部空格误判正确');
 await page.fill('#fill-answer',' cout ');await page.click('#fill-check');check(await page.getAttribute('#fill-feedback','data-correct')==='true','允许前后空白');
 await page.check('[name="lesson-answer"][value="0"]');await page.click('#quiz-check');await page.reload();await page.waitForFunction(()=>document.querySelectorAll('#lesson-menu a').length>0&&!document.querySelector('#fill-check').disabled);
 check(await page.inputValue('#fill-answer')===' cout '&&await page.getAttribute('#fill-feedback','data-correct')==='true','填空与反馈恢复');
 check(await page.isChecked('[name="lesson-answer"][value="0"]')&&(await page.textContent('#quiz-feedback')).includes('答对'),'选择题与反馈恢复');
 await page.check('[name="lesson-answer"][value="1"]');check(!(await page.textContent('#quiz-feedback')).includes('答对'),'改答案后清除旧成功提示');
 for(const e of data.lessons){
  await page.evaluate(id=>location.hash='lesson='+id,e.id);await page.waitForFunction(t=>document.querySelector('#lesson-title').textContent===t,e.title);
  for(const answer of e.fill.accepted){await page.fill('#fill-answer',answer);await page.click('#fill-check');check(await page.getAttribute('#fill-feedback','data-correct')==='true','代码填空 '+e.id+' '+answer);}
  check((await page.textContent('#practice-focus')).includes(e.practice.focus)&&await page.locator('#practice-checks li').count()===2,'实操定位与边界 '+e.id);
 }
 await go('output');await page.click('#run-help>summary');await page.selectOption('#run-environment','windows');check((await page.textContent('#run-command')).includes('tools/study.py run'),'Windows运行命令');
 await page.selectOption('#run-environment','linux');check((await page.textContent('#run-command')).includes('tools/wsl-study.py run'),'Linux运行命令');
 check((await page.textContent('#practice-stdin')).trim()==='1','菜单输入独立展示');
 await go('checks');await page.click('#run-help>summary');await page.selectOption('#run-environment','linux');
 check((await page.textContent('#run-command')).includes('ctest --test-dir')&&!(await page.textContent('#run-command')).includes('study.py run'),'库文件使用CMake而非单文件运行');
 await page.selectOption('#run-environment','windows');check((await page.textContent('#run-command')).trim()==='wsl -d Ubuntu-22.04','Windows项目入口先转到WSL');
 for(const [w,h,name] of [[820,1180,'平板'],[390,844,'手机']]){
  await page.setViewportSize({width:w,height:h});await go('functions');check(await page.isVisible('#lesson-quicknav'),name+'底部导航');
  await page.click('#quick-fill');check(await page.evaluate(()=>document.activeElement.id)==='fill-card',name+'快速填空定位');
  await page.click('#quick-practice');check(await page.evaluate(()=>document.activeElement.id)==='practice-card',name+'快速实操定位');
  await page.click('#quick-directory');check(await page.getAttribute('#lesson-directory','open')!==null,name+'快速选课');
  check(!await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth),name+'无横向溢出');
  await page.click('#lesson-directory>summary');await page.click('#quick-fill');await page.screenshot({path:OUT+'/填空与快捷导航-'+name+'.png'});
 }
 await page.click('#quick-next');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='函数接口：形参、实参与返回值');check(true,'底部下一节切换');
 await page.route('**/cpp-lessons.json',r=>r.fulfill({status:503,body:'unavailable'}));await page.reload();await page.waitForSelector('#lesson-retry:not([hidden])');check(await page.isDisabled('#copy-example'),'加载失败时禁用依赖课程的操作');
 await page.unroute('**/cpp-lessons.json');await page.click('#lesson-retry');await page.waitForFunction(()=>document.querySelectorAll('#lesson-menu a').length>0&&!document.querySelector('#fill-check').disabled);check(true,'加载失败可重试恢复');
 check(errors.length===0,'无前端错误 '+errors.join('|'));fs.writeFileSync(OUT+'/结果.json',JSON.stringify({checks,errors},null,2));
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1});


