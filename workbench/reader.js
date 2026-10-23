/* Marked只负责词法分析；用DOM白名单创建阅读内容，不插入原始HTML。 */
(()=>{
 const decode=s=>String(s??'').replace(/&(#x[\da-f]+|#\d+|amp|lt|gt|quot|apos);/gi,(_,v)=>{
   const named={amp:'&',lt:'<',gt:'>',quot:'"',apos:"'"};if(named[v.toLowerCase()])return named[v.toLowerCase()];
   const n=parseInt(v.slice(v[1]?.toLowerCase()==='x'?2:1),v[1]?.toLowerCase()==='x'?16:10);return n>0&&n<=0x10ffff?String.fromCodePoint(n):'�';
 });
 const node=(tag,text)=>{const e=document.createElement(tag);if(text!==undefined)e.textContent=text;return e};
 const chineseRoots={'C++学习':'cpp','机器视觉学习':'opencv','高等数学学习':'math','Linux学习':'linux','计算机基础':'fundamentals','图形学原理':'graphics','OpenGL实践':'opengl','操作系统学习':'os','编译器学习':'compiler','图神经网络学习':'gnn','使用指南':'guide'};
 function canonical(path){if(typeof path!=='string')return path;const parts=path.split('/');parts[0]=chineseRoots[parts[0]]||parts[0];return parts.join('/')}
 function readable(value){const path=canonical(value);return typeof path==='string'&&path.length<512&&!/[\\%?#:]/.test(path)&&!path.startsWith('/')&&path.split('/').every(p=>p&&!p.startsWith('.'))&&(['README.md','学习区使用说明.md','工作区入口/README.md'].includes(path)||/^(guide|math|cpp|linux|opencv|graphics|opengl|os|compiler|gnn|network|fundamentals)\/.+\.md$/i.test(path)||path==='workbench/使用说明.md')}
 function documentUrl(value){const path=canonical(value);if(!readable(path))return null;const chapter=path.match(/^cpp\/主教材\/章节学习\/第(\d{2})章\/原书阅读\.md$/);if(chapter&&+chapter[1]>=1&&+chapter[1]<=20)return '/workbench/chapter.html?chapter='+Number(chapter[1]);return '/workbench/help.html?doc='+encodeURIComponent(path)}
 function readingUrl(u){if(u.origin!==location.origin)return u.href;try{const path=decodeURIComponent(u.pathname).replace(/^\//,'');const mapped=documentUrl(path);return mapped?mapped+u.hash:u.href}catch{return u.href}}
 function url(href,base){try{const u=new URL(href,base);return ['http:','https:'].includes(u.protocol)?u:null}catch{return null}}
 function inline(tokens,parent,base){for(const t of tokens||[]){
   if(t.type==='strong'||t.type==='em'||t.type==='del'){const e=node(t.type==='strong'?'strong':t.type==='em'?'em':'del');inline(t.tokens||[{type:'text',text:t.text}],e,base);parent.append(e)}
   else if(t.type==='codespan')parent.append(node('code',t.text));
   else if(t.type==='br')parent.append(node('br'));
   else if(t.type==='html'&&/^\s*<a\s+id="[a-zA-Z][\w-]{0,79}"\s*>(?:<\/a>)?\s*$/.test(t.raw)){const a=node('span');a.id=t.raw.match(/id="([^"]+)"/)[1];parent.append(a)}
   else if(t.type==='html'&&/^\s*<\/a>\s*$/.test(t.raw))continue;
   else if(t.type==='image'){const u=url(t.href,base);if(u&&/\.(png|jpe?g|gif|svg|webp)$/i.test(u.pathname)){
     // 原文里的插图直接画出来（懒加载），点图片看原尺寸；alt 放图注。
     const fig=node('figure');fig.className='reading-figure';const img=node('img');img.src=u.href;img.alt=decode(t.text||'');img.loading='lazy';img.decoding='async';img.referrerPolicy='no-referrer';const a=node('a');a.href=u.href;a.target='_blank';a.rel='noopener noreferrer';a.append(img);fig.append(a);if(t.text){const cap=node('figcaption',decode(t.text));fig.append(cap)}img.onerror=()=>{const link=node('a','查看图示：'+decode(t.text||''));link.href=u.href;link.target='_blank';link.rel='noopener noreferrer';fig.replaceWith(link)};parent.append(fig)
   }else{const a=node(u?'a':'span');if(u){a.href=u.href;a.target='_blank';a.rel='noopener noreferrer'}a.textContent='查看图示：'+decode(t.text);parent.append(a)}}
   else if(t.type==='link'){const u=url(t.href,base);const a=node(u?'a':'span');if(u){a.href=readingUrl(u);a.target='_blank';a.rel='noopener noreferrer'}inline(t.tokens||[{type:'text',text:t.text}],a,base);parent.append(a)}
   else if(t.type==='text'&&t.tokens)inline(t.tokens,parent,base);
   else parent.append(document.createTextNode(decode(t.text??t.raw??'')));
 }}
 function blocks(tokens,parent,base){for(const t of tokens||[]){
   if(t.type==='space'||(t.type==='html'&&/^\s*<!--[\s\S]*?-->\s*$/.test(t.raw)))continue;
   if(t.type==='heading'){const e=node('h'+Math.max(1,Math.min(6,t.depth)));inline(t.tokens,e,base);parent.append(e)}
   else if(t.type==='paragraph'||t.type==='text'){const e=node('p');inline(t.tokens||[{type:'text',text:t.text}],e,base);parent.append(e)}
   else if(t.type==='code'){const pre=node('pre'),code=node('code',t.text);if(t.lang)code.dataset.language=t.lang.slice(0,40);pre.append(code);parent.append(pre)}
   else if(t.type==='list'){const list=node(t.ordered?'ol':'ul');if(t.ordered&&Number.isSafeInteger(t.start)&&t.start>0)list.start=t.start;for(const item of t.items){const li=node('li');if(item.task)li.append(document.createTextNode(item.checked?'[已勾选] ':'[待办] '));blocks(item.tokens,li,base);list.append(li)}parent.append(list)}
   else if(t.type==='blockquote'){const e=node('blockquote');blocks(t.tokens,e,base);parent.append(e)}
   else if(t.type==='table'){const wrap=node('div'),table=node('table'),head=node('thead'),row=node('tr');wrap.className='table-scroll';if(t.header.length>2){wrap.classList.add('wide-table');wrap.tabIndex=0;wrap.setAttribute('role','region');wrap.setAttribute('aria-label','表格，可左右滚动')}for(const cell of t.header){const th=node('th');th.scope='col';inline(cell.tokens,th,base);row.append(th)}head.append(row);table.append(head);const body=node('tbody');for(const values of t.rows){const tr=node('tr');for(const cell of values){const td=node('td');inline(cell.tokens,td,base);tr.append(td)}body.append(tr)}table.append(body);wrap.append(table);if(t.header.length>2){const note=node('p','宽表格可左右滑动；键盘可聚焦表格后用方向键滚动。');note.className='table-scroll-hint';parent.append(note)}parent.append(wrap)}
   else if(t.type==='html'&&/^\s*<a\s+id="[a-zA-Z][\w-]{0,79}"\s*><\/a>\s*$/.test(t.raw)){const a=node('span');a.id=t.raw.match(/id="([^"]+)"/)[1];parent.append(a)}
   else if(t.type==='hr')parent.append(node('hr'));
   else parent.append(node('p',t.raw??t.text??''));
 }}
 function polish(target){const ids=new Set();for(const e of target.querySelectorAll('[id]'))ids.add(e.id);for(const h of target.querySelectorAll('h1,h2,h3,h4,h5,h6')){const base=h.textContent.trim().toLowerCase().replace(/[^\p{L}\p{N}\s_-]/gu,'').replace(/\s+/g,'-')||'section';let id=base,n=1;while(ids.has(id))id=base+'-'+n++;h.id=id;h.tabIndex=-1;ids.add(id)}
  for(const pre of target.querySelectorAll('pre')){const code=pre.querySelector('code');if(!code)continue;pre.tabIndex=0;pre.setAttribute('aria-label','代码，可左右滚动');const bar=node('div');bar.className='reading-codebar';const language=node('span',code.dataset.language||'文本'),copy=node('button','复制代码');copy.type='button';copy.setAttribute('aria-label','复制这段代码');copy.onclick=async()=>{try{await navigator.clipboard.writeText(code.textContent);copy.textContent='已复制'}catch{copy.textContent='请手动选择复制'}};bar.append(language,copy);pre.before(bar)}
 }
 window.BookReader={isReadable:readable,documentUrl,readingUrl,render(target,text,path){if(!window.marked?.lexer)return false;try{const fragment=document.createDocumentFragment();blocks(window.marked.lexer(text,{gfm:true}),fragment,new URL('/'+path,location.origin));target.replaceChildren(fragment);polish(target);return true}catch{return false}}};
})();
