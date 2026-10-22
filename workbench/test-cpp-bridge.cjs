const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');
(async()=>{
 const out='D:/工作区/工作区/learning-update/cpp-learning-bridge';
 const browser=await chromium.launch({channel:'msedge',headless:true,args:['--no-proxy-server']});const errors=[],checks=[];
 const check=(ok,label)=>{if(!ok)throw Error(label);checks.push(label);console.log('PASS '+label)};
 try{
 const p=await browser.newPage({viewport:{width:1440,height:1000}});p.on('pageerror',e=>errors.push(e.message));
 const data=await(await p.request.get('http://127.0.0.1:18765/workbench/cpp-lessons.json')).json();
 await p.goto('http://127.0.0.1:18765/workbench/cpp-tutorial.html');await p.waitForFunction(()=>document.querySelectorAll('#lesson-menu a').length>0&&!document.querySelector('#fill-check').disabled);
 for(const e of data.lessons){
  await p.evaluate(id=>location.hash='lesson='+id,e.id);await p.waitForFunction(t=>document.querySelector('#lesson-title').textContent===t,e.title);
  check(await p.textContent('#lesson-pitfall')===e.pitfall,'易错点 '+e.id);
  check(!await p.locator('#pitfall-card').evaluate(e=>e.open),'易错提醒默认收起 '+e.id);
  if(e.practice.steps){
   check(await p.locator('#practice-steps li').count()===3,'分步实操 '+e.id);
   const model=data.practice_models.find(m=>m.id===e.practice.model);
   check(await p.textContent('#practice-model-code')===model.code&&await p.textContent('#practice-model-output')===model.output,'整合参考对应 '+e.id);
   await p.locator('#practice-model-card>summary').click();check(await p.locator('#practice-model-code').isVisible(),'按需展开参考 '+e.id);
  }else check(!await p.locator('#practice-model-card').isVisible(),'不混入其他小节参考 '+e.id);
 }
 await p.evaluate(()=>location.hash='lesson=methods');await p.waitForFunction(()=>document.querySelector('#lesson-title').textContent.startsWith('方法'));
 await p.locator('#practice-steps-card>summary').click();await p.locator('#practice-model-card>summary').click();
 await p.locator('#practice-card').scrollIntoViewIfNeeded();await p.screenshot({path:out+'/对象实操-电脑.png'});
 await p.setViewportSize({width:820,height:1180});check(!await p.locator('#lesson-directory').evaluate(e=>e.open),'窄屏自动收起目录');
 await p.locator('#practice-steps-card').scrollIntoViewIfNeeded();check(!await p.evaluate(()=>document.documentElement.scrollWidth>innerWidth),'平板无横向溢出');await p.screenshot({path:out+'/对象实操-平板.png'});
 await p.setViewportSize({width:390,height:844});check(!await p.evaluate(()=>document.documentElement.scrollWidth>innerWidth),'手机无横向溢出');
 check(errors.length===0,'无脚本异常');fs.writeFileSync(out+'/界面验收.json',JSON.stringify({checks,errors},null,2));
 }finally{await browser.close()}
})().catch(e=>{console.error(e);process.exitCode=1});

