"""本机学习工作台；仅开放学习目录中的只读资料与进度记录。"""
import csv, io, json, os, subprocess, threading, re, socket, hashlib, sys
from urllib.request import build_opener, ProxyHandler
from pathlib import Path
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler
from urllib.parse import urlparse, unquote, parse_qs, quote

from pdf_range import serve_pdf
import original_reader
from path_compat import current_path

ROOT = Path(__file__).resolve().parents[1]
# 端口可用环境变量覆盖，默认 18765；端口被占用时换一个即可。
PORT = int(os.environ.get('BOOK_STUDY_PORT', '18765'))
HERE = Path(__file__).resolve().parent
LOCK = threading.Lock()
EXERCISE_LOCK = threading.Lock()
TRACKS = [
 ('fundamentals','计算机基础（图灵四册）','硬件、程序、对象、网络的通识底座，读在具体语言之前。','fundamentals-four.epub','fundamentals','01'),
 ('cpp','C++ 程序设计','当前主教材：Roberts《C++程序设计：基础、编程抽象与算法策略》20章；五册书作为参考。','cpp-roberts.pdf',None,'02'),
 ('linux','Linux 与 Shell','从命令行入门，到脚本与数据处理。','linux-shell.pdf',None,'03'),
 ('graphics','计算机图形学原理','C 语言描述：几何、变换与绘制算法。','graphics-c.pdf',None,'04'),
 ('opengl','OpenGL 图形实践','配合原理学习，从三角形走向三维场景。','opengl.epub','opengl','05'),
 ('opencv','OpenCV 计算机视觉','英文原书，配套中文导读、练习和解析。','opencv-learning.epub','opencv','06'),
 ('os','操作系统实践（30天自制）','从启动扇区写到窗口与多任务，把计算机基础落到硬件上。','os30.pdf',None,'07'),
 ('compiler','编译器','先《自制编译器》建直觉，再用《编译器构造》补理论体系。','compiler-mini.pdf',None,'08'),
 ('gnn','图神经网络（GNN）','从图与神经网络基础，走到 GCN/GAT/GraphSAGE 与应用。','gnn.epub',None,'09'),
 ('math','斯图尔特微积分','微分方程、极坐标、极限优先，之后重点推进下册；编程为选做。','calculus-stewart.pdf',None,'10')]
# 主线附带的补充教材入口（按主线 id 索引）
EXTRA_BOOKS={'fundamentals':[('network-how.pdf','《网络是怎样连接的》独立 PDF（362页，可查页码）')],
 'compiler':[('compiler-cbc.pdf','《编译器构造 C语言描述》（理论补充，548页）')],
 'cpp':[('cpp-five.epub','C++五册参考教材（保留原有练习）')]}
def access_settings():
 try:
  settings=json.loads((HERE/'access.json').read_text(encoding='utf-8'))
  origins=settings.get('origins',[])
  allowed=[]
  for origin in origins:
   u=urlparse(origin)
   if u.scheme=='https' and u.hostname and u.hostname.endswith('.ts.net') and u.netloc and not u.username and not u.password and not u.path and not u.query and not u.fragment:
    allowed.append(origin)
  return dict(origins=allowed,workbench_url=settings.get('workbench_url',''),editor_url=settings.get('editor_url',''))
 except (OSError,ValueError,TypeError):return dict(origins=[],workbench_url='',editor_url='')

def access_status():
 settings=access_settings();ready=False
 try:
  with build_opener(ProxyHandler({})).open('http://127.0.0.1:18766/',timeout=.8) as response:ready=response.status==200
 except Exception:pass
 return dict(workbench_url=settings['workbench_url'],editor_url=settings['editor_url'],editor_ready=ready,source_root='仓库根目录',wsl_root='仓库根目录')

def row_revision(row):
 return hashlib.sha256(json.dumps(row,ensure_ascii=False,sort_keys=True).encode()).hexdigest()

def safe(rel):
 p=(ROOT/current_path(rel)).resolve()
 if not p.is_relative_to(ROOT) or any(x in p.relative_to(ROOT).parts for x in ('vendor','build','.git','tools','.remote-vscode','.remote-vscode-cli')): raise ValueError('此路径不属于可浏览的学习资料')
 return p
def registered_work(work):
 """这道文件是不是某道题登记过的作答。

 同一道题有两份并列作答：work.cpp（补充型）与 from-scratch.cpp（从零写），
 两份都要能判分。比对必须按 resolve() 后的真实路径：登记里写的是数字目录
 （第02章/课后习题/第06题），页面上传的是带名字的目录，字面比较会对不上。
 """
 work=str(work or '')
 if not work:return False
 try:target=(ROOT/work).resolve()
 except OSError:return False
 rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
 for e in rules:
  for key in (e.get('work'),e.get('work_scratch')):
   if not key:continue
   try:
    if (ROOT/key).resolve()==target:return True
   except OSError:continue
 return False


def progress():
 # 学习进度是个人数据，公开仓库里没有这个文件；缺了就当“还没开始”，
 # 不能让整个目录接口跟着挂掉。
 path=ROOT/'guide/学习进度.csv'
 if not path.is_file():return []
 with path.open(encoding='utf-8-sig',newline='') as f:return list(csv.DictReader(f))
def catalog():
 answer_rules={str((ROOT/e['work']).resolve()):e for e in json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))}
 labs=json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8-sig'))
 tests=json.loads((ROOT/'tools/book-tests.json').read_text(encoding='utf-8-sig'))
 fundamentals=json.loads((ROOT/'tools/fundamentals-index.json').read_text(encoding='utf-8'))
 rows=[]
 for e in labs:
  folder=Path(e['source']).parent; track=folder.parts[0]; ch=e['chapter']
  rows.append(dict(id=e['id'],track=track,title=ch['title'],kind=e['kind'],folder=folder.as_posix(),guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=e['source'],bookpage=ch.get('pdf_page'),href=ch.get('href')))
 for e in tests:
  folder=Path(e['source']).parent
  # dict.get 的默认值会被无条件求值，所以不能把“解析 id”写在第二个参数里：
  # 那样任何 id 不是 xxx-chNN-NN 的条目（比如综合项目）都会让整个目录接口报错。
  title=e.get('title')
  if not title:
   parts=e['id'].split('-')
   try:
    chapter=int(parts[1][2:]);number=int(parts[2])
    title='PPP 第%d章 · 习题 %d' % (chapter,number)
   except (IndexError,ValueError):
    title=e['id']
  rows.append(dict(id=e['id'],track='cpp',title=title,kind=('综合项目' if '-project' in e['id'] else '原书习题'),folder=folder.as_posix(),guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=e['source'],bookpage=e.get('pdf_page')))
 for e in json.loads((ROOT/'tools/roberts-index.json').read_text(encoding='utf-8')):
  folder=Path(e['folder'])
  rows.append(dict(id=e['id'],track='cpp',title=e['title'],kind='配套练习',folder=e['folder'],guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=(folder/'reference.cpp').as_posix(),bookpage=e['pdf_page']))
 for e in json.loads((ROOT/'tools/vision-book-index.json').read_text(encoding='utf-8')):
  folder=Path(e['folder'])
  rows.append(dict(id=e['id'],track='opencv',title=e['title'],kind='原书习题',folder=e['folder'],guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=(folder/'reference.cpp').as_posix(),href=e['href']))
 for e in fundamentals:
  folder=Path(e['folder']).resolve().relative_to(ROOT)
  rows.append(dict(id=e['id'],track='fundamentals',title=e['title'],kind='配套练习',folder=folder.as_posix(),guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=(folder/'reference.c').as_posix(),href=e['href'],bookpage=e.get('pdf_page')))
 # 新主线：按各自索引文件驱动
 for track in ('gnn','os','compiler'):
  for e in json.loads((ROOT/('tools/%s-index.json'%track)).read_text(encoding='utf-8')):
   folder=Path(e['folder']).resolve().relative_to(ROOT)
   rows.append(dict(id=e['id'],track=track,title=e['title'],kind='配套练习',folder=folder.as_posix(),guide=(folder/'README.md').as_posix(),answer=(folder/'solution.md').as_posix(),source=(folder/'reference.c').as_posix(),bookpage=e.get('pdf_page')))
 for ident,track,title,folder,src in [('linux-score-report','linux','综合项目：成绩报告','linux/projects/score-report','reference.sh'),('opencv-image-pipeline','opencv','综合项目：图像处理工具','opencv/projects/image-pipeline','main.cpp'),('opengl-camera-lab','opengl','综合项目：三维变换与轨道相机','opengl/projects/camera-lab','reference.cpp'),('linux-dataset-audit','linux','综合项目：图像数据集盘点','linux/projects/dataset-audit','reference.sh'),('opencv-parts-inspector','opencv','综合项目：零件轮廓计数与报告','opencv/projects/parts-inspector','reference.cpp')]:
  answer=folder+'/solution.md' if (ROOT/folder/'solution.md').exists() else folder+'/'+src
  rows.append(dict(id=ident,track=track,title=title,kind='综合项目',folder=folder,guide=folder+'/README.md',answer=answer,source=folder+'/'+src))
 for e in json.loads((ROOT/'tools/calculus-index.json').read_text(encoding='utf-8')):
  rows.append(dict(id=e['id'],track='math',title=e['title'],kind=e['kind'],folder=e['folder'],guide=e['folder']+'/README.md',answer=e['folder']+'/solution.md',source=e['source'],bookpage=e['pdf_page']))
 ids={r['题号'] for r in progress()}
 # 索引里可能有条目指向本机不存在的目录（公开副本只带了一部分学科）。
 # 缺一个条目就跳过它，不要让整个 /api/catalog 变成 404。
 rows=[r for r in rows if (ROOT/r['folder']/'README.md').is_file()]
 for r in rows:
  chapter_dir=ROOT/r['folder']
  guide_text=(chapter_dir/'README.md').read_text(encoding='utf-8-sig')
  heading=re.search(r'^#\s+(.+)',guide_text,re.M)
  if heading and r['track'] in ('os','compiler','gnn'):r['title']=heading.group(1)
  book_match=re.search(r'books/([\w-]+\.pdf)',guide_text)
  track_info=next(t for t in TRACKS if t[0]==r['track'])
  r['book']='books/'+(book_match.group(1) if book_match else track_info[3])
  reader_root='reader/'+track_info[4] if track_info[4] else None
  if r['track']=='cpp':
   primary=r['source'].startswith('cpp/主教材/')
   r['book']='books/cpp-roberts.pdf' if primary else 'books/cpp-five.epub'
   r['role']='当前主教材' if primary else '参考教材'
   chapter=re.match(r'(?:ROB-L|roberts-ch)(\d+)',r['id'])
   if primary and chapter:r['chapter_guide']='cpp/主教材/章节学习/第'+chapter.group(1).zfill(2)+'章/README.md'
   reader_root=None if primary else 'reader/cpp-five'
  r['reading']=reader_root+'/'+r['href'] if reader_root and r.get('href') else r['book']+('#page='+str(r['bookpage']) if r.get('bookpage') else '')
  r['original']='workbench/original.html#page='+str(r['bookpage']) if r['track']=='cpp' and r.get('bookpage') and r['book']=='books/cpp-roberts.pdf' else None
  if r['original'] and r.get('chapter_guide'):
   r['original']='workbench/chapter.html?chapter='+str(int(chapter.group(1)))+'#page='+str(r['bookpage'])
  # 下拉框只给“可以动手的文件”。参考答案、解析、给定头文件都不列，
  # 否则学生一打开下拉就能看到答案。
  hidden_files={'reference.cpp','reference.c','reference.sh','solution.md','lesson.h','notes.md','README.md'}
  r['files']=[{'path':p.relative_to(ROOT).as_posix(),'label':p.name} for p in sorted(chapter_dir.iterdir()) if p.is_file() and p.name not in hidden_files and (p.suffix in ('.c','.cpp','.sh','.h','.hpp') or p.name=='CMakeLists.txt')]
  r['work']=next((p.relative_to(ROOT).as_posix() for name in ('我的作答/main.cpp','work/main.cpp','work/main.c','work.cpp','work.c','work.sh') if (p:=chapter_dir/name).is_file()),None)
  if r['work'] and (rule:=answer_rules.get(str((ROOT/r['work']).resolve()))):
   r['work']=rule['work'];r['guide']=rule['guide'];r['check']=rule['check']
   if rule.get('work_files'):r['work_files']=rule['work_files']
   # 同一道题两份并列作答：补写版只填空，从零写整份自己写。两份都能判分，
   # 页面上的文件下拉就是这两项，选哪个就判哪个。
   if rule.get('work_scratch'):
    r['work_files']=[{'path':r['work'],'label':'补写版 · work.cpp','editable':True},
                     {'path':rule['work_scratch'],'label':'从零写 · from-scratch.cpp','editable':True}]
  r['scope']={'os':'宿主端概念模拟，非裸机系统','opengl':'章节概念练习；真实 GPU 示例见 first-triangle','gnn':'C 语言概念实现，非深度学习框架训练'}.get(r['track'],'章节练习与参考实现')
  if r['id'] in ('roberts-ch02-16','roberts-ch02-17','roberts-ch02-18'):
   r['scope']='原书静态图形要求的SVG教学适配；使用图形专项验收，非Stanford原生图形窗口'
   if (chapter_dir/'运行结果/reference.png').exists():r['previews']=[{'path':r['folder']+'/运行结果/reference.png','label':'参考图形预览'}]
  if r['id']=='opengl-camera-lab':
   r['scope']='真实 OpenGL GPU 项目：变换、轨道相机、深度测试与简单方向光'
   r['previews']=[{'path':r['folder']+'/output/'+name+'.png','label':'参考渲染：'+label} for name,label in [('view-a','视角 A'),('view-b','视角 B')] if (chapter_dir/'output'/(name+'.png')).exists()]
  if r['id']=='opencv-parts-inspector':r['scope']='机器视觉教学项目：阈值分割与轮廓计数，非神经网络检测器'
  if r['track']=='math':r['scope']='数学导读/选题/自编练习分别标注；原书解析覆盖以清单为准，编程为选做'
  if r['id'] not in ids:
   matches=[p for p in progress() if p['任务类型']=='综合项目' and r['track'] in p['题号'].lower()]
   if len(matches)==1:r['id']=matches[0]['题号']
 priorities={'cpp':0,'opencv':1,'math':2}
 ordered=sorted(TRACKS,key=lambda t:priorities.get(t[0],3+int(t[5])))
 rows.sort(key=lambda r:(priorities.get(r['track'],3+next(int(t[5]) for t in TRACKS if t[0]==r['track'])),r.get('role')=='参考教材'))
 # 同章相邻题：题目页能直接翻上一题/下一题，不用回章节页重新点。
 _groups={}
 for r in rows:
  m=re.search(r'第(\d+)章',r.get('folder') or '')
  _groups.setdefault((r['track'],m.group(1) if m else (r.get('folder') or '')),[]).append(r)
 for _group in _groups.values():
  _group.sort(key=lambda r:(r.get('folder') or '',r['id']))
  for _i,_row in enumerate(_group):
   _row['prev']=_group[_i-1]['id'] if _i>0 else None
   _row['next']=_group[_i+1]['id'] if _i+1<len(_group) else None
 return dict(tracks=[dict(id=t[0],name=t[1],description=t[2],focus=t[0] in priorities,book='books/'+t[3],reader='reader/'+t[4]+'/index.html' if t[4] else None,number=t[5],extra_books=[{'path':'books/'+p,'label':l} for p,l in EXTRA_BOOKS.get(t[0],[])]) for t in ordered],items=rows,progress=[dict(r,_revision=row_revision(r)) for r in progress()])
class Handler(SimpleHTTPRequestHandler):
 def __init__(self,*args,**kw):super().__init__(*args,directory=str(ROOT),**kw)
 def end_headers(self):
  self.send_header('X-Content-Type-Options','nosniff');super().end_headers()
 def result(self,obj,status=200):
  data=json.dumps(obj,ensure_ascii=False).encode();self.send_response(status);self.send_header('Content-Type','application/json; charset=utf-8');self.send_header('Content-Length',str(len(data)));self.end_headers();self.wfile.write(data)
 def do_GET(self):
  url=urlparse(self.path)
  try:
   previous=unquote(url.path).lstrip('/')
   current=current_path(previous)
   if current!=previous:
    self.send_response(307);self.send_header('Location','/'+quote(current,safe='/')+('?' + url.query if url.query else ''));self.end_headers();return
   if url.path=='/api/catalog':return self.result(catalog())
   if url.path=='/api/access':return self.result(access_status())
   if url.path=='/api/health':return self.result({'app':'book-learning-workbench'})
   if url.path=='/api/original/manifest':return self.result(original_reader.manifest())
   match=re.fullmatch(r'/api/original/page/(\d{1,3})\.png',url.path)
   if match:
    scale=(parse_qs(url.query).get('scale') or [original_reader.DEFAULT_SCALE])[0]
    image,_,_=original_reader.page_image(int(match.group(1)),scale)
    return original_reader.send_png(self,image)
   match=re.fullmatch(r'/api/original/text/(\d{1,3})',url.path)
   if match:return self.result(original_reader.page_text(int(match.group(1))))
   match=re.fullmatch(r'/api/original/figure/([^/]+\.png)',url.path)
   if match:return original_reader.send_png(self,original_reader.figure_path(unquote(match.group(1))))
   if url.path=='/':self.path='/workbench/index.html'
   path=safe(unquote(urlparse(self.path).path).lstrip('/'))
   if path.is_dir():self.send_error(403);return
   if path.suffix.lower() in ('.md','.cpp','.c','.h','.hpp','.sh','.txt','.csv'):
    data=path.read_text(encoding='utf-8-sig').encode('utf-8');self.send_response(200);self.send_header('Content-Type','text/plain; charset=utf-8');self.send_header('Content-Length',str(len(data)));self.end_headers();self.wfile.write(data);return
   if path.suffix.lower()=='.pdf':return serve_pdf(self,path)
   return super().do_GET()
  except (ValueError,FileNotFoundError) as e:self.result({'error':str(e)},404)
 def do_HEAD(self):
  try:
   url=urlparse(self.path);previous=unquote(url.path).lstrip('/');current=current_path(previous)
   if current!=previous:
    self.send_response(307);self.send_header('Location','/'+quote(current,safe='/')+('?' + url.query if url.query else ''));self.end_headers();return
   path=safe(unquote(urlparse(self.path).path).lstrip('/'))
   if path.is_dir():self.send_error(403);return
   if path.suffix.lower()=='.pdf':return serve_pdf(self,path,head=True)
   return super().do_HEAD()
  except (ValueError,FileNotFoundError):self.send_error(404)
 def do_POST(self):
  try:
   origin=self.headers.get('Origin')
   local_origins=(None,'http://127.0.0.1:%d'%PORT,'http://localhost:%d'%PORT)
   if origin not in local_origins and origin not in access_settings()['origins']:raise ValueError('请求来源不允许')
   if self.headers.get('Content-Type')!='application/json':raise ValueError('需要 JSON 请求')
   n=int(self.headers.get('Content-Length','0'))
   if not 0<n<8192:raise ValueError('请求大小不正确')
   body=json.loads(self.rfile.read(n));path=urlparse(self.path).path
   if path=='/api/progress':
    if body.get('status') not in ('未开始','学习中','已完成'):raise ValueError('状态无效')
    with LOCK:
     rows=progress();row=next((r for r in rows if r['题号']==body['id']),None)
     if row is None:raise ValueError('未找到这条学习记录')
     if 'revision' in body and body['revision']!=row_revision(row):return self.result({'error':'这条记录已在其他页面更新。当前复盘仍在输入框中，请先复制保留，再刷新并重新打开本题后合并。'},409)
     from datetime import date
     row['状态']=body['status'];row['复盘']=str(body.get('note',row['复盘']))[:2000]
     if body['status']!='未开始' and not row['开始日期']:row['开始日期']=date.today().isoformat()
     row['完成日期']=date.today().isoformat() if body['status']=='已完成' else ''
     dest=ROOT/'guide/学习进度.csv';tmp=dest.with_suffix('.csv.tmp')
     with tmp.open('w',encoding='utf-8-sig',newline='') as f:
      w=csv.DictWriter(f,fieldnames=list(rows[0]));w.writeheader();w.writerows(rows)
     os.replace(tmp,dest)
    return self.result({'ok':True})
   if path=='/api/open':
    if origin not in local_origins:return self.result({'error':'平板请使用网页作答入口；电脑窗口操作仅在本机页面提供。'},403)
    p=safe(body['path'])
    if not p.exists():raise ValueError('文件不存在')
    if body.get('mode')=='answer':
     rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
     rule=next((e for e in rules if (ROOT/e['work']).resolve()==p),None)
     if rule is None:raise ValueError('请选择已登记的个人作答文件')
     edit=safe(rule.get('edit',rule['work']))
     if not edit.is_file() or not edit.is_relative_to(p.parent):raise ValueError('作答编辑文件不在本题目录')
     subprocess.Popen(['D:/Microsoft VS Code/Code.exe','--new-window',str(p.parent),str(edit)])
    elif body.get('mode')=='code':
     subprocess.Popen(['D:/Microsoft VS Code/Code.exe','--new-window',str(p)])
    elif body.get('mode')=='wsl':
     if p!=ROOT/'workspaces/focus-wsl.code-workspace':raise ValueError('请选择已配置的WSL联合工作区')
     subprocess.Popen(['D:/Microsoft VS Code/Code.exe','--new-window','--remote','wsl+Ubuntu-22.04','仓库根目录/workspaces/focus-wsl.code-workspace'])
    elif p.is_dir():os.startfile(str(p))
    else:raise ValueError('只允许打开目录或 VS Code 工作区')
    return self.result({'ok':True})
   if path in ('/api/exercise/run','/api/exercise/check'):
    return self.exercise(path.endswith('/check'),body,origin,local_origins)
   if path=='/api/exercise/mode':
    return self.exercise_mode(body,origin,local_origins)
   if path=='/api/exercise/hidden':
    return self.exercise_hidden(body,origin,local_origins)
   raise ValueError('未知操作')
  except Exception as e:self.result({'error':str(e)},400)
 def exercise_hidden(self,body,origin,local_origins):
  """用没登记过的输入对照参考实现；只接受已登记的作答路径。"""
  allowed=set(local_origins)|set(access_settings()['origins'])
  if origin not in allowed:return self.result({'error':'这个来源没有授权。'},403)
  work=str(body.get('work') or '')
  rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
  if not registered_work(work):raise ValueError('只能检查已登记的作答文件')
  target=(ROOT/work).resolve()
  if not target.is_relative_to(ROOT) or not target.is_file():raise ValueError('作答文件不存在')
  try:
   with EXERCISE_LOCK:
    child_env=dict(os.environ, PYTHONIOENCODING='utf-8', PYTHONUTF8='1')
    proc=subprocess.run([sys.executable,str(ROOT/'tools/hidden-check.py'),str(target)],
                        cwd=str(ROOT),capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=180,env=child_env)
   out=(proc.stdout or '')+(proc.stderr or '')
   state={0:'agree',1:'differ',2:'unsupported',3:'unfinished',4:'compile-error'}.get(proc.returncode,'error')
   return self.result({'state':state,'log':out[:6000]})
  except subprocess.TimeoutExpired:
   return self.result({'state':'timeout','log':'隐藏样例检查超过 180 秒，已终止。'})
 def exercise_mode(self,body,origin,local_origins):
  """查看或切换这道题的作答模式：引导版 / 从零写。

  只接受已登记的作答路径；切换由 tools/switch-mode.py 完成，服务端不自己改文件。
  """
  allowed=set(local_origins)|set(access_settings()['origins'])
  if origin not in allowed:return self.result({'error':'这个来源没有授权。'},403)
  work=str(body.get('work') or '')
  rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
  rule=next((e for e in rules if e['work']==work),None)
  if rule is None:raise ValueError('只能切换已登记的作答文件')
  target=(ROOT/work).resolve()
  if not target.is_relative_to(ROOT) or not target.is_file():raise ValueError('作答文件不存在')
  modes=json.loads((ROOT/'tools/exercise-modes.json').read_text(encoding='utf-8')) if (ROOT/'tools/exercise-modes.json').is_file() else {}
  key=target.relative_to(ROOT.resolve()).as_posix()
  # 综合项目这类题设计上就只有「从零写」，没有骨架可给：不显示切换按钮，
  # 也不允许切过去，否则会用空模板盖掉学生已经写好的代码。
  blank_only=bool(rule.get('blank_only'))
  # 已经有并存的 from-scratch.cpp 时，“切换模式”就没意义了：
  # 点一下只会覆盖 work.cpp，而第二份作答本来就在那儿。
  dual=bool(rule.get('work_scratch'))
  want=str(body.get('mode') or '')
  if want not in ('blank','guided'):
   return self.result({'mode':modes.get(key,'guided'),'hasTemplate':not (blank_only or dual),'blankOnly':blank_only})
  if (want=='guided' and blank_only) or dual:
   raise ValueError('本题没有引导版，只能从零写')
  child_env=dict(os.environ, PYTHONIOENCODING='utf-8', PYTHONUTF8='1')
  flag='--blank' if want=='blank' else '--guided'
  proc=subprocess.run([sys.executable,str(ROOT/'tools/switch-mode.py'),str(target),flag],
                      cwd=str(ROOT),capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=60,env=child_env)
  note=(proc.stdout or proc.stderr or '').strip().split('\n')[-1]
  if proc.returncode!=0:raise ValueError(note or '切换失败')
  modes=json.loads((ROOT/'tools/exercise-modes.json').read_text(encoding='utf-8')) if (ROOT/'tools/exercise-modes.json').is_file() else {}
  key=target.relative_to(ROOT.resolve()).as_posix()
  return self.result({'mode':modes.get(key,'guided'),'note':note})
 def exercise(self,checking,body,origin,local_origins):
  """运行或检查一份已登记的个人作答；不接受任意路径，也不接受任意命令。"""
  # 平板经私有域名访问时也要能检查：本地来源 + access.json 里已授权的 https 来源。
  allowed=set(local_origins)|set(access_settings()['origins'])
  if origin not in allowed:return self.result({'error':'这个来源没有授权。请在电脑上把设备加入允许列表，或直接在电脑上操作。'},403)
  work=str(body.get('work') or '')
  if len(work)>400:raise ValueError('路径过长')
  rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
  if not registered_work(work):raise ValueError('只能运行或检查已登记的个人作答文件；参考实现与样例数据不能当作自己的作答。')
  target=(ROOT/work).resolve()
  if not target.is_relative_to(ROOT) or not target.is_file():raise ValueError('作答文件不存在')
  tool='check-current.py' if checking else 'run-current.py'
  args=[sys.executable,str(ROOT/'tools'/tool),str(target)]
  used_input=False
  if not checking:
   sample=target.parent/'input.txt'
   if sample.is_file():
    args.append('--input');used_input=True
  try:
   with EXERCISE_LOCK:
    # 显式让子进程用 UTF-8 输出：服务可能由不同方式启动，系统默认编码不一定是 UTF-8。
    child_env=dict(os.environ, PYTHONIOENCODING='utf-8', PYTHONUTF8='1')
    proc=subprocess.run(args,cwd=str(ROOT),capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=180,env=child_env)
   code,out,err=proc.returncode,proc.stdout,proc.stderr
  except subprocess.TimeoutExpired:
   return self.result({'action':'check' if checking else 'run','code':None,'state':'timeout','stdout':'','stderr':'','samples':None,'detail':'运行超过180秒仍未结束，已终止。可能是程序进入死循环，请检查循环条件。'})
  # 工具会输出一行机器可读状态，优先用它判断，不去猜中文措辞。
  state_info=None
  marker=re.search(r'^##STATE##\s*(\{.*\})\s*$',out or '',re.M)
  if marker:
   try:state_info=json.loads(marker.group(1))
   except (ValueError,TypeError):state_info=None
   out=re.sub(r'^##STATE##.*$\n?','',out,flags=re.M)
  trunc=lambda t:(t or '')[:12000]
  result={'action':'check' if checking else 'run','code':code,'stdout':trunc(out),'stderr':trunc(err),'samples':None,'detail':'','usedInput':used_input}
  if checking:
   if state_info and state_info.get('state'):
    state=state_info['state']
    detail_map={'unfinished':'作答还是空模板，没有比较任何样例。',
                'compile-error':'编译失败，一组样例都没有运行。',
                'passed':'登记样例全部通过；仍是固定样例，不等于所有情况都正确。',
                'failed':'有样例未通过，请对照输入、期望与实际结果。',
                'manual':'本题没有自动判分，需要按说明逐项人工自检。',
                'unregistered':'本题尚未接入统一检查入口。'}
    result['detail']=detail_map.get(state,'检查没有正常完成，请看下方输出。')
    if state=='unfinished':
     line=next((l for l in out.splitlines() if '本题尚未开始作答' in l),'')
     if '：' in line:result['detail']=line.split('：',1)[1].rstrip('。')
    if 'total' in state_info:
     total=state_info['total'] or 0;okn=state_info.get('passed',0)
     result['samples']={'passed':okn,'failed':max(0,total-okn),'total':total}
   else:
    # 老工具没有机器状态时，退回文本判断；不改宽松条件。
    manual_hint=('没有独立自动判分' in out) or ('没有独立自动评分' in out)
    if manual_hint:
     state,result['detail']='manual','本题没有自动判分，需要按说明逐项人工自检。'
    elif code==3:
     line=next((l for l in out.splitlines() if '本题尚未开始作答' in l),'')
     state='unfinished'
     result['detail']=(line.split('：',1)[1].rstrip('。') if '：' in line else '作答还是空模板，没有比较任何样例。')
    elif code==4:state,result['detail']='compile-error','编译失败，一组样例都没有运行。'
    elif code==0:state,result['detail']='passed','登记样例全部通过；仍是固定样例，不等于所有情况都正确。'
    elif code==1:state,result['detail']='failed','有样例未通过，请对照输入、期望与实际结果。'
    elif code==2 and '还没有登记判分规则' in out:state,result['detail']='unregistered','本题尚未接入统一检查入口。'
    else:state,result['detail']='error','检查没有正常完成，请看下方输出。'
    ok_count=len(re.findall(r'样例\d+：通过',out));bad_count=len(re.findall(r'样例\d+：未通过',out))
    if ok_count or bad_count:result['samples']={'passed':ok_count,'failed':bad_count,'total':ok_count+bad_count}
  else:
   state='ran'
   result['detail']=('已用本题 input.txt 作为标准输入运行；这一步只运行程序，不判题。' if used_input else '没有 input.txt，按空输入运行；这一步只运行程序，不判题。') if code==0 else '程序退出码不是0；这还不等于题目未通过，请看输出。'
  result['state']=state
  return self.result(result)
class LocalServer(ThreadingHTTPServer):
 allow_reuse_address=False
 def server_bind(self):
  if hasattr(socket,'SO_EXCLUSIVEADDRUSE'):self.socket.setsockopt(socket.SOL_SOCKET,socket.SO_EXCLUSIVEADDRUSE,1)
  super().server_bind()
if __name__=='__main__':
 LocalServer(('127.0.0.1',PORT),Handler).serve_forever()
