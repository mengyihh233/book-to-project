(()=>{'use strict';
 const $=id=>document.getElementById(id),make=(tag,text)=>{const e=document.createElement(tag);if(text!==undefined)e.textContent=text;return e},a=(label,url)=>{const e=make('a',label);e.href=url;return e};
 const names={cpp:'C++学习',opencv:'机器视觉学习',math:'高等数学学习',linux:'Linux学习'},q=new URLSearchParams(location.search),track=q.get('track')||'cpp',number=Number(q.get('chapter')||0),base='/workbench/course.html?track='+encodeURIComponent(track),doc=p=>'/workbench/help.html?doc='+encodeURIComponent(p),task=e=>'/#task='+encodeURIComponent(e.id);
 function bread(title){const b=$('course-breadcrumb');b.replaceChildren(a('学习首页','/workbench/directory.html'),make('span','›'),a(names[track],base));if(title)b.append(make('span','›'),make('span',title));}
 function row(title,sub,url,state){const link=a('',url);link.className='course-row';const text=make('span');text.append(make('strong',title));if(sub)text.append(make('small',sub));const tail=make('span');tail.className='course-tail';if(state&&state!=='未开始'){const dot=make('i');dot.className='course-state '+(state==='已完成'?'is-done':'is-doing');dot.setAttribute('title',state);dot.setAttribute('aria-label',state);tail.append(dot);}tail.append(make('span','→'));link.append(text,tail);return link;}
 function step(title,text,links){const box=make('section');box.className='course-step';box.append(make('h2',title),make('p',text));const actions=make('div');actions.className='actions';for(const [label,url] of links)actions.append(a(label,url));if(actions.firstChild)actions.firstChild.classList.add('primary');box.append(actions);return box;}
 function manual(e){return e.check==='book'?'固定样例比较':e.check==='svg'?'图形专项检查':'按题目自检';}
 async function load(){
  $('course-retry').hidden=true;$('course-status').textContent='正在读取章节和题目…';
  const control=new AbortController(),timer=setTimeout(()=>control.abort(),8000);
  try{
   if(!names[track])throw Error('请选择首页中的学习学科');
   const [r,ci]=await Promise.all([fetch('/api/catalog',{signal:control.signal}),fetch('/workbench/study-structure.json',{signal:control.signal})]);if(!r.ok||!ci.ok)throw Error('目录读取失败');const data=await r.json(),cpp=(await ci.json()).chapters;
   // 每题的状态直接取目录接口里的进度，不在页面里另存一份。
   const done={};for(const p of data.progress||[])if(p['状态']&&p['状态']!=='未开始')done[p['题号']]=p['状态'];
   const items=data.items.filter(e=>e.track===track&&e.role!=='参考教材'),groups=[];
   if(track==='cpp')for(const ch of cpp){groups.push({n:ch.number,title:ch.title,items:items.filter(e=>e.id==='ROB-L'+String(ch.number).padStart(2,'0')||e.id.startsWith('roberts-ch'+String(ch.number).padStart(2,'0')+'-'))});}
   else if(track==='math'){for(const e of items.filter(e=>e.id.startsWith('MATH-U-')))groups.push({n:groups.length+1,title:e.title,items:[e]});}
   else for(const main of items.filter(e=>new RegExp('^'+track+'-L\\d+$').test(e.id))){const n=Number(main.id.match(/\d+$/)[0]);groups.push({n,title:main.title,items:[main,...items.filter(e=>e!==main&&e.id.startsWith(track+'-book-ch'+String(n).padStart(2,'0')+'-'))]});}
   const content=$('course-content');content.replaceChildren();bread();document.title=names[track]+' · 章节与练习';
   if(number){
    const group=groups.find(g=>g.n===number);if(!group)throw Error('没有这个章节，请返回学科目录选择');bread(group.title);$('course-title').textContent=group.title;$('course-lead').textContent='先读这一章，再选一种练习。每道题里都有自己的作答位置与检查方式。';
    // 第16—20章没有逐题整理的原书习题，只有综合项目。不能把项目当成“章内综合练习”，
    // 否则 main 抢走了它，“本章项目”分组永远是空的。
    const practice=group.items.filter(e=>e.kind!=='综合项目');
    const main=practice.find(e=>/^ROB-L|^[a-z]+-L/.test(e.id))||practice[0]||null;
    const readingLinks=[[track==='cpp'?'阅读本章原文':'阅读本章说明',track==='cpp'?'/workbench/chapter.html?chapter='+number:doc((main||group.items[0]).guide)]];
    if(track==='cpp'){
     // 例题讲解只有部分章写了；有才显示入口，避免点进去是空页。
     const example='cpp/主教材/章节学习/第'+String(number).padStart(2,'0')+'章/例题讲解.md';
     try{if((await fetch('/'+example,{method:'HEAD'})).ok)readingLinks.push(['本章例题与讲解',doc(example)]);}catch{}
    }
    if(track==='opencv'){
     // OpenCV 的原书是 EPUB，没有 PDF 页码，走不了 chapter.html 的按页阅读；
     // 直接用文档页读“原文 / 中文导读”，两份都在章节目录里。
     const dir='opencv/chapters/ch'+String(number).padStart(2,'0');
     readingLinks[0]=['阅读本章原文',doc(dir+'/原书阅读.md')];
     try{if((await fetch('/'+dir+'/中文导读.md',{method:'HEAD'})).ok)readingLinks.push(['中文导读',doc(dir+'/中文导读.md')]);}catch{}
    }
    content.append(step('1 · 阅读教材',track==='cpp'?'本章原文按小节连续阅读；例题讲解用来对照书上的示例。':'先读本章中文说明和教材定位。',readingLinks));
    // main 为空说明这一章只有综合项目，练习步骤改成提示，链接留给下面的“本章项目”。
    const own=step('2 · 选择练习',main?(track==='cpp'?'章内综合练习将本章重点放在一起；原书课后题按原书题号排列。按需选择，不要求重复全做。':'打开配套练习，按照题目完成自己的实现。'):'本章没有逐题整理的原书习题，直接做下面的项目；需要补概念就回上面读原文。',main?[[track==='cpp'?'章内综合练习':'本章配套练习',task(main)]]:[]);content.append(own);
    if(track==='cpp'){
     // 把“这一章能顺带练哪个库”接到本章，学生不用去翻折叠里的总表。
     try{
      const lib=await fetch('/workbench/library-practice.json',{cache:'no-store'}).then(x=>x.ok?x.json():null);
      const mine=lib?(lib.groups||[]).filter(g=>(g.chapters||[]).includes(number)):[];
      if(mine.length){
       own.append(make('h3','本章可顺带练的库'));
       const box=make('div');box.className='library-groups';
       for(const g of mine){
        const row=make('div');row.className='library-group';
        const text=make('span');text.append(make('strong',g.name));text.append(make('small',g.lib+' · 写 '+g.file.split('/').pop()));
        row.append(text);box.append(row);
       }
       own.append(box);
       const more=a('打开这 '+mine.length+' 组的说明','/workbench/help.html?doc='+encodeURIComponent(lib.guide));
       more.className='library-more';own.append(more);
      }
     }catch{}
     // 语法小课按知识点接到本章，避免 32 节散在折叠里没入口。
     try{
      const grammar=await fetch('/workbench/grammar-map.json',{cache:'no-store'}).then(x=>x.ok?x.json():null);
      const lessons=grammar?((grammar.chapters||{})[String(number)]||[]):[];
      if(lessons.length){
       own.append(make('h3','本章可补的语法课'));
       const box=make('div');box.className='library-groups';
       for(const item of lessons){
        const link=a('',doc(item.file));link.className='library-group';
        link.append(make('strong',item.title),
                    make('small',item.file.split('/').pop().replace(/\.md$/,'')),
                    make('span','→'));
        box.append(link);
       }
       own.append(box);
      }
     }catch{}
    }
    // 综合项目不从属于“原书课后习题”的编号序列，单独一组放在最后，
    // 否则它的 id 末尾不是数字，排序键会变成 0 而排到最前面。
    const items=group.items.filter(e=>e!==main);
    const projects=items.filter(e=>e.kind==='综合项目');
    const after=items.filter(e=>e.kind!=='综合项目').sort((a,b)=>Number(a.id.match(/(\d+)$/)?.[1]||0)-Number(b.id.match(/(\d+)$/)?.[1]||0));if(after.length){const h=make('h3','原书课后习题'),list=make('div');list.className='course-list';
     for(const [i,e] of after.entries()){
      // 整页都是第 N 章，标题里再重复“第N章习题”是噪音；只留题号 + 练什么。
      // 标题实际形如 "Roberts 第3章习题1：后缀判断与重载"，先去作者前缀再去章节前缀。
      const raw=String(e.title||'').trim().replace(/^Roberts\s*/,'');
      const num=(raw.match(/习题\s*(\d+)/)||[])[1]||String(i+1);
      const label=raw.replace(/^\s*第\d+章[\s·]*习题\s*\d+\s*[：:]\s*/,'')||raw;
      list.append(row(num+' · '+label,e.check==='book'?'':manual(e),task(e),done[e.id]));
     }
     own.append(h,list);}else if(track==='cpp')own.append(make('p',main?'本章课后题尚未逐题整理；章内综合练习可直接使用。':'本章课后题尚未逐题整理。'));
    if(projects.length){const h=make('h3','本章项目'),list=make('div');list.className='course-list';
     for(const e of projects){
      const name=String(e.title||'').replace(/^第\d+章\s*项目[：:]\s*/,'');
      list.append(row('项目 · '+name,'从零写，不给样例',task(e),done[e.id]));
     }
     own.append(h,list);}
    content.append(make('p','选题后，在题目页打开自己的作答。运行与检查使用相同的日常任务名称。'));
    content.append(a('← 返回'+names[track]+'章节目录',base));
   }else{
    $('course-title').textContent=names[track];$('course-lead').textContent=track==='cpp'?'日常按章节学习。小课用于补基础，库练习用于集中查练，不是额外三遍必做任务。':track==='math'?'优先微分方程、极坐标、极限，再继续下册专题。文字题在对应空位写解答，人工核对。':'选择一章，阅读说明后再进入具体练习。';
    const list=make('div');list.className='course-list';list.setAttribute('aria-label','章节与专题');for(const g of groups)list.append(row(g.title,'阅读 → 选题 → 自己的作答',track==='cpp'?base+'&chapter='+g.n:task(g.items[0])));content.append(list);
    const extra=make('details');extra.append(make('summary','按需使用：基础、项目与工具'));const links=make('div');links.className='course-step';
    if(track==='cpp')links.append(a('语法小课 · 补基础','/workbench/cpp-tutorial.html'),make('p','概念不熟时查小课；做完回到正在学的章节。'),a('常用库练习 · 同库集中练',doc('cpp/主教材/常用库练习/README.md')));
    if(track==='math')links.append(a('数学可视化','/workbench/calculus.html'));
    if(track==='opencv')links.append(a('视觉失败场景实验','/workbench/vision-lab.html'));
    for(const e of items.filter(e=>e.kind==='综合项目'))links.append(make('p'),a(e.title,task(e)));
    links.append(make('p'),a('环境与操作说明',doc('guide/环境配置教程/README.md')));extra.append(links);content.append(extra);
   }
   $('course-status').textContent='';
  }catch(e){$('course-title').textContent='章节暂未打开';$('course-status').textContent=e.message+'。可以重试或返回学习首页。';$('course-retry').hidden=false;}
  finally{clearTimeout(timer);}
 }
 $('course-retry').onclick=load;load();
})();
