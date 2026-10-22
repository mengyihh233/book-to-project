window.StudyAccess=(()=>{
 const remote=!['localhost','127.0.0.1','[::1]'].includes(location.hostname);let settings={};
 const url=value=>{try{const u=new URL(value);return u.protocol==='https:'&&u.hostname.endsWith('.ts.net')&&!u.username&&!u.password?u:null}catch{return null}};
 async function load(){const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),3500);try{const r=await fetch('/api/access',{signal:controller.signal});if(!r.ok)throw Error('读取失败');settings=await r.json()}catch{settings={error:true}}finally{clearTimeout(timer)}}
 function anchor(text,href){const a=document.createElement('a');a.textContent=text;a.href=href;a.target='_blank';a.rel='noopener noreferrer';return a}
 function editorAction(folder=''){const base=url(settings.editor_url);if(!base||!settings.editor_ready){const b=document.createElement('button');b.textContent='网页作答尚未就绪';b.disabled=true;return b}base.searchParams.set('folder','/仓库根目录'+(folder?'/'+folder:''));return anchor('在网页 VS Code 作答',base.href)}
 function taskUrl(id){const base=url(settings.workbench_url)||new URL(location.origin);base.hash='task='+encodeURIComponent(id);return base.href}
 function render(){const el=document.querySelector('#connection');if(!el)return;const panel=document.querySelector('#connection-panel');if(panel&&!panel.dataset.initialized){panel.open=remote;panel.dataset.initialized='true'}const h=document.createElement('strong');h.textContent=remote?'平板 / 远程学习':'电脑本机学习';const p=document.createElement('p');p.textContent=settings.error?'连接状态暂时读取失败，教材与学习任务仍可使用。':settings.editor_ready?'读题 → 网页作答 → 终端检查 → 回到本题复盘。作答与进度保存在同一台电脑。':'学习资料可用；网页编辑器尚未就绪，启动电脑上的联合学习入口后再刷新连接。';
 const actions=document.createElement('div');actions.className='actions';actions.append(editorAction(),anchor('平板使用说明','/workbench/help.html?doc='+encodeURIComponent('guide/平板联动快速上手.md')),anchor('网页版VS Code手册','/workbench/help.html?doc='+encodeURIComponent('guide/VSCode网页版使用手册.md')));
 if(!remote&&url(settings.workbench_url))actions.append(anchor('平板工作台地址',settings.workbench_url));
 const refresh=document.createElement('button');refresh.textContent='刷新连接';refresh.onclick=async()=>{refresh.disabled=true;refresh.textContent='检查连接中…';await load();render()};
 const sync=document.createElement('button');sync.id='sync-progress';sync.textContent='刷新共享进度';sync.onclick=async()=>{try{const r=await fetch('/api/catalog');if(!r.ok)throw Error('读取失败');const d=await r.json();window.dispatchEvent(new CustomEvent('study-progress',{detail:d.progress}))}catch{window.dispatchEvent(new CustomEvent('study-progress-error'))}};
 actions.append(refresh,sync);el.replaceChildren(h,p,actions)}
 return{remote,load,render,editorAction,taskUrl};
})();
