/* 填空只检查固定槽位，不执行用户代码；运行命令只由用户复制到对应终端。 */
window.QuickPractice=(()=>{
 const $=id=>document.getElementById(id),KEY='cpp-quickcourse-v1:answer:';
 let current;
 const read=()=>{try{const v=JSON.parse(localStorage.getItem(KEY+current.id));return v&&typeof v==='object'?v:{}}catch{return {}}};
 const save=v=>{try{localStorage.setItem(KEY+current.id,JSON.stringify(v))}catch{}};
 const normalize=s=>String(s).trim();
 function loading(value){for(const id of ['example-tab','edit-tab','copy-example','quiz-check','lesson-done','lesson-editor','lesson-search','lesson-scope','fill-answer','fill-check','copy-run','quick-directory','quick-fill','quick-practice','quick-next'])$(id).disabled=value;}
 function quizFeedback(v){
  if(!v.checked)return;
  const ok=v.choice===current.quiz.answer;
  $('quiz-feedback').dataset.correct=String(ok);$('quiz-feedback').textContent=ok?'答对了。'+current.quiz.reason:'还不对，再对照示例想一想；可展开提示与解释。';
 }
 function fillFeedback(v){
  if(!v.fillChecked)return;
  const ok=current.fill.accepted.some(a=>normalize(a)===normalize(v.fill));
  $('fill-feedback').dataset.correct=String(ok);$('fill-feedback').textContent=ok?'填对了。'+current.fill.reason:'还不对。只填空缺部分，留意大小写、命名空间和符号；可展开提示。';
 }
 function saveQuiz(choice,checked){const v=read();v.choice=choice;v.checked=checked;save(v);}
 function commands(){
  const env=$('run-environment').value,p=current.practice;
  let command;
  if(p.project){
   if(env==='windows'){command='wsl -d Ubuntu-22.04';$('run-note').textContent='先用这条命令进入Ubuntu，再切换上方到“Ubuntu / WSL终端”。该文件是库实现，不能当成单文件程序运行。';}
   else {const build='"$HOME/.cache/book-learning/cmake/rational-work-cn"';command='cd 仓库根目录\ncmake -S "cpp/主教材/综合项目/有理数与CMake" -B '+build+' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBOOK_USE_REFERENCE=OFF\ncmake --build '+build+' --parallel 2\nctest --test-dir '+build+' --output-on-failure';$('run-note').textContent='检查的是自己的实现。出现NOT_IMPLEMENTED通常表示还未作答；细节按项目说明核对。';}
  } else {
   command=env==='windows'?"cd 仓库根目录\n& 'C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe' tools/study.py run '"+p.path+"'":"cd 仓库根目录\npython3 tools/wsl-study.py run '"+p.path+"'";
   $('run-note').textContent='先保存源码，再在选定环境执行。命令只编译运行所示文件；程序启动后再输入菜单号和数据。';
  }
  $('run-command').textContent=command;$('practice-stdin-block').hidden=!p.stdin;$('practice-stdin').textContent=p.stdin||'';
 }
 function show(lesson){
  current=lesson;loading(false);$('lesson-retry').hidden=true;
  const v=read(),radio=[...document.querySelectorAll('input[name="lesson-answer"]')].find(el=>Number(el.value)===v.choice);if(radio)radio.checked=true;quizFeedback(v);
  $('fill-card').hidden=!current.fill;
  if(current.fill){$('fill-prompt').textContent=current.fill.prompt;$('fill-snippet').textContent=current.fill.snippet;$('fill-answer').value=typeof v.fill==='string'?v.fill:'';$('fill-feedback').textContent='';delete $('fill-feedback').dataset.correct;$('fill-hint').textContent=current.fill.accepted.join(' 或 ')+'。'+current.fill.reason;fillFeedback(v);}
  $('practice-focus').textContent='修改位置：'+current.practice.focus;$('practice-checks').replaceChildren(...current.practice.checks.map(text=>{const li=document.createElement('li');li.textContent=text;return li;}));
  $('run-help').open=false;commands();$('quick-next').disabled=!$('lesson-next').getAttribute('href')||$('lesson-next').hidden;
 }
 $('quiz-options').addEventListener('change',()=>{const selected=document.querySelector('input[name="lesson-answer"]:checked');if(!current||!selected)return;saveQuiz(Number(selected.value),false);$('quiz-feedback').textContent='答案已更改，请重新检查。';delete $('quiz-feedback').dataset.correct;});
 $('quiz-check').addEventListener('click',()=>{const selected=document.querySelector('input[name="lesson-answer"]:checked');if(current&&selected)saveQuiz(Number(selected.value),true);});
 $('fill-answer').oninput=()=>{if(!current)return;const v=read();v.fill=$('fill-answer').value;v.fillChecked=false;save(v);$('fill-feedback').textContent='';delete $('fill-feedback').dataset.correct;};
 $('fill-check').onclick=()=>{if(!current)return;const v=read();v.fill=$('fill-answer').value;if(!v.fill.trim()){$('fill-feedback').textContent='先填入缺少的代码。';return;}v.fillChecked=true;save(v);fillFeedback(v);};
 $('fill-answer').onkeydown=e=>{if(e.key==='Enter'){e.preventDefault();$('fill-check').click();}};
 $('run-environment').onchange=commands;
 $('copy-run').onclick=async()=>{try{await navigator.clipboard.writeText($('run-command').textContent);$('run-note').textContent='命令已复制；请确认终端环境后手动粘贴运行。';}catch{$('run-note').textContent='剪贴板不可用，可手动选择上方命令复制。';}};
 $('quick-directory').onclick=()=>{$('lesson-directory').open=true;$('lesson-directory').scrollIntoView({block:'start'});$('lesson-search').focus({preventScroll:true});};
 for(const [button,target]of [['quick-fill','fill-card'],['quick-practice','practice-card']])$(button).onclick=()=>{$(target).scrollIntoView({block:'start'});$(target).focus({preventScroll:true});};
 $('quick-next').onclick=()=>{if(!$('lesson-next').hidden)location.hash=$('lesson-next').hash;};
 $('lesson-retry').onclick=()=>location.reload();
 loading(true);
 return{show,saveQuiz,failed(){loading(true);$('lesson-retry').hidden=false;$('lesson-retry').disabled=false;}};
})();
