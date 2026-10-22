const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');const BASE='http://127.0.0.1:18765',OUT='D:/工作区/工作区/learning-update/cpp-core-concepts/界面验收';
(async()=>{
 fs.mkdirSync(OUT,{recursive:true});const browser=await chromium.launch({channel:'msedge',headless:true,args:['--no-proxy-server']});const errors=[],checks=[];let posts=0;
 const check=(ok,label)=>{if(!ok)throw Error(label);checks.push(label);console.log('PASS '+label)};
 try{
 const page=await browser.newPage({viewport:{width:1440,height:1000}});page.on('pageerror',e=>errors.push(e.message));page.on('request',r=>{if(r.method()==='POST')posts++;});
 await page.addInitScript(()=>{if(!localStorage.getItem('core-test-seeded')){localStorage.setItem('cpp-quickcourse-v1',JSON.stringify({done:['output','classes'],last:'output'}));localStorage.setItem('cpp-quickcourse-v1:code:output',JSON.stringify('// old personal draft'));localStorage.setItem('core-test-seeded','1');}});
 const data=await(await page.request.get(BASE+'/workbench/cpp-lessons.json')).json();
 async function go(id){await page.goto(BASE+'/workbench/cpp-tutorial.html'+(id?'#lesson='+id:''));await page.waitForFunction(()=>document.querySelectorAll('#lesson-menu a').length>0&&!document.querySelector('#fill-check').disabled);}
 await go();check(await page.locator('#lesson-menu a').count()===24,'默认基础24节');
 check((await page.textContent('#lesson-progress')).includes('2 / 32'),'旧已练记录保留');await page.click('#edit-tab');check(await page.inputValue('#lesson-editor')==='// old personal draft','旧代码草稿保留');
 await page.selectOption('#lesson-scope','all');check(await page.locator('#lesson-menu a').count()===32,'全部32节可选');
 await page.selectOption('#lesson-scope','core');await page.fill('#lesson-search','形参');check((await page.textContent('#lesson-menu')).includes('函数接口'),'按概念关键词查课');await page.fill('#lesson-search','');
 await page.click('#concept-desk>summary');check(await page.locator('.concept-entry').count()===27,'27个基础概念速查');await page.fill('#concept-search','形参');check(await page.locator('.concept-entry').count()>=1,'概念速查可筛选');
 await page.locator('.concept-entry a').first().click();await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='函数接口：形参、实参与返回值');check(true,'概念直接链接到讲解与实操');
 for(const e of data.lessons){
  await page.evaluate(id=>location.hash='lesson='+id,e.id);await page.waitForFunction(t=>document.querySelector('#lesson-title').textContent===t,e.title);
  await page.check('[name="lesson-answer"][value="'+e.quiz.answer+'"]');await page.click('#quiz-check');check((await page.textContent('#quiz-feedback')).includes('答对'),'概念小测 '+e.id);
  await page.fill('#fill-answer',e.fill.accepted[0]);await page.click('#fill-check');if(await page.getAttribute('#fill-feedback','data-correct')!=='true')throw Error('填空 '+e.id);
  check(await page.locator('#practice-checks li').count()===2&&!!await page.getAttribute('#lesson-book-source a','href'),'实操与原书联系 '+e.id);
 }
 await go('ownership');check(await page.inputValue('#lesson-scope')==='all','旧进阶深链接仍然有效');
 await page.selectOption('#lesson-scope','core');await page.waitForFunction(()=>document.querySelector('#lesson-title').textContent==='程序、输出与换行');check(true,'从进阶可回基础路线');
 await go('references');await page.selectOption('#lesson-scope','core');check((await page.getAttribute('#lesson-next','href'))==='#lesson=strings','基础下一节跳过按需补充');
 await go('types');await page.screenshot({path:OUT+'/类型教学-电脑.png'});
 for(const [w,h,name]of [[820,1180,'平板'],[390,844,'手机']]){
  await page.setViewportSize({width:w,height:h});await go('constructors');check(!await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth),name+'无横向溢出');await page.screenshot({path:OUT+'/构造函数-'+name+'.png'});
 }
 check(posts===0,'不改共享进度或自动打开编辑器');check(errors.length===0,'无脚本错误 '+errors.join('|'));
 fs.writeFileSync(OUT+'/结果.json',JSON.stringify({checks,errors,posts},null,2));
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1});


