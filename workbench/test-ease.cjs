const {chromium}=require('C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/playwright');
const fs=require('fs');
const BASE='http://127.0.0.1:18765',OUT='D:/工作区/工作区/learning-update/workbench-ease/界面验收';
(async()=>{
 fs.mkdirSync(OUT,{recursive:true});
 const browser=await chromium.launch({headless:true,channel:'msedge',args:['--no-proxy-server']});
 const errors=[],fails=[],checks=[];
 const check=(ok,label)=>{console.log((ok?'PASS ':'FAIL ')+label);checks.push(label);if(!ok)fails.push(label)};
 try{
 const page=await browser.newPage({viewport:{width:1440,height:1000}});page.on('pageerror',e=>errors.push(e.message));
 await page.goto(BASE);await page.waitForSelector('.book');
 await page.locator('#nav button').filter({hasText:'C++ 程序设计'}).click();
 check(await page.locator('.chapter-card:visible').count()===6,'默认六章入口避免长列表');
 check(await page.locator('.task').count()===101,'101项主教材任务仍保留');
 await page.locator('.chapter-more').click();check(await page.locator('.chapter-card:visible').count()===20,'展开全部20章');
 await page.locator('.chapter-card').nth(1).getByRole('button').click();
 check(await page.locator('#chapter-filter').inputValue()==='ch02','从章节进入第2章练习');
 check(await page.locator('.task').count()===19,'第2章仅显示本章19项任务');
 await page.reload();await page.waitForSelector('.task');
 check(await page.locator('#track-choice').inputValue()==='cpp'&&await page.locator('#chapter-filter').inputValue()==='ch02','刷新保留学习区与章节筛选');
 await page.goto(BASE+'/#task=ROB-L02');await page.waitForSelector('#detail[open]');
 check((await page.textContent('#task-work-location')).includes('我的作答/main.cpp'),'准确提示学生作答位置');
 check(await page.locator('#chapter-files button:has-text("查看我的作答")').count()===1,'嵌套作答文件也能预览');
 check(!await page.locator('#chapter-files details').first().getAttribute('open'),'补充资料默认收起');
 check(!await page.locator('#chapter-files details').last().getAttribute('open'),'参考代码默认收起');
 await page.locator('#note').fill('易用性验收草稿：仅浏览器暂存，不写共享进度');
 await page.locator('#edit-status').selectOption('学习中');
 await page.locator('#close').click();
 await page.waitForURL(url=>!url.hash.includes('task='));
 check(!page.url().includes('task='),'关闭详情清除旧题深链接');
 await page.goto(BASE+'/#task=ROB-L02');await page.waitForSelector('#detail[open]');
 check((await page.inputValue('#note')).includes('易用性验收草稿')&&await page.inputValue('#edit-status')==='学习中','关闭刷新恢复未保存复盘与进度选择');
 check((await page.textContent('#draft-status')).includes('本机'),'草稿明确标记本机状态');
 // 不向真实服务保存任何测试进度；拦截保存接口与刷新读取。
 const snapshot=await(await page.request.get(BASE+'/api/catalog')).json();
 const clone=structuredClone(snapshot);const record=clone.progress.find(r=>r['题号']==='ROB-L02');
 record['状态']='学习中';record['复盘']=await page.inputValue('#note');record._revision='ease-test-revision';
 await page.route('**/api/progress',r=>r.fulfill({status:200,contentType:'application/json',body:'{"ok":true}'}));
 await page.route('**/api/catalog',r=>r.fulfill({status:200,contentType:'application/json',body:JSON.stringify(clone)}));
 await page.click('#save');await page.waitForFunction(()=>document.querySelector('#draft-status').textContent.includes('已保存到学习区'));
 check(await page.evaluate(()=>localStorage.getItem('study-desk-draft-v1:ROB-L02'))===null,'成功保存后清除草稿（拦截模拟，未写真实进度）');
 await page.unroute('**/api/progress');await page.unroute('**/api/catalog');
 await page.screenshot({path:OUT+'/题目详情-电脑.png'});
 await page.keyboard.press('Escape');
 await page.locator('#nav button').filter({hasText:'Linux 与 Shell'}).click();
 check(await page.locator('#chapter-filter-label').isVisible(),'Linux章节筛选可用');
 check(await page.locator('.chapter-card').count()===26,'Linux26章导航');
 check(await page.locator('#cpp-book').isHidden()&&await page.locator('#scope').isHidden(),'本区隐藏不相关的教材和主线筛选');
 await page.locator('.chapter-card').nth(1).getByRole('button').click();
 check(await page.locator('.task').count()===1,'Linux按章筛选');
 await page.locator('#nav button').filter({hasText:'OpenCV'}).click();
 check((await page.locator('.chapter-card h3').nth(2).textContent()).includes('基本数据类型'),'OpenCV章节中文名称');
 await page.screenshot({path:OUT+'/章节导航-电脑.png'});
 const own=await(await page.request.get(BASE+'/api/catalog')).json();
 const item=own.items.find(e=>e.id==='opencv-L03');
 check(item.work.endsWith('我的作答/main.cpp'),'OpenCV自己的作答被识别');
 await page.goto(BASE+'/#task=opencv-L03');await page.waitForSelector('#detail[open]');
 await page.locator('#chapter-files button:has-text("查看我的作答")').click();
 await page.waitForFunction(()=>document.querySelector('#doc-path').textContent.endsWith('我的作答/main.cpp'));
 check(true,'自己的代码预览可用');
 await page.keyboard.press('Escape');
 for(const [w,h,name]of [[1024,768,'平板横屏'],[820,1180,'平板竖屏'],[390,844,'手机']]){
  await page.setViewportSize({width:w,height:h});
  await page.evaluate(()=>document.querySelector('#chapter-browser').scrollIntoView());
  check(!await page.evaluate(()=>document.documentElement.scrollWidth>innerWidth),name+'无横向溢出');
  await page.screenshot({path:OUT+'/章节导航-'+name+'.png'});
 }
 await page.goto(BASE+'/#task=ROB-L02');await page.waitForSelector('#detail[open]');
 check(!await page.evaluate(()=>document.querySelector('#detail').scrollWidth>document.querySelector('#detail').clientWidth),'手机详情无横向溢出');
 await page.screenshot({path:OUT+'/题目详情-手机.png'});
 await page.keyboard.press('Escape');await page.click('#theme');
 check(await page.evaluate(()=>document.documentElement.dataset.theme)==='dark','深色主题仍可切换');
 check(errors.length===0,'无前端脚本错误 '+errors.join('|'));
 fs.writeFileSync(OUT+'/结果.json',JSON.stringify({checks,fails,errors,realProgressWrites:0},null,2));
 if(fails.length)throw Error(fails.join(';'));
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1});

