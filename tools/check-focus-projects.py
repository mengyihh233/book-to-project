"""重点项目真实验收：合成图有已知对象，失败输入有固定退出约定。"""
import json,hashlib,time,os
from pathlib import Path
from PIL import Image,ImageDraw
from study import ROOT,build,call
base=ROOT/'build/focus-verification'/str(time.time_ns());base.mkdir(parents=True)
data=base/'中文 图片';data.mkdir();image=Image.new('RGB',(400,300),'white');d=ImageDraw.Draw(image);d.rectangle((30,40,90,110),fill='black');d.ellipse((150,80,230,160),fill='black');d.rectangle((280,150,350,250),fill='black');d.rectangle((5,5,7,7),fill='black');sample=data/'零件 图.PNG';image.save(sample)
blank=data/'空白.png';Image.new('RGB',(400,300),'white').save(blank);bad=data/'坏图.jpg';bad.write_bytes(b'not an image')
hashes={p:hashlib.sha256(p.read_bytes()).hexdigest() for p in data.iterdir()};rows=[]
def record(name,ok,details=''):
 rows.append({'name':name,'passed':bool(ok),'details':details});print(name,'PASS' if ok else 'FAIL',flush=True)
exe=build(ROOT/'opencv/projects/parts-inspector/reference.cpp')
for n,extra,source,code,count in [('三件与噪点过滤',{},sample,0,3),('空白图',{},blank,0,0),('高面积过滤',{'min_area':9000},sample,0,0),('坏图',{},bad,2,None),('阈值非法',{'threshold':256},sample,2,None),('面积区间非法',{'min_area':1000,'max_area':200},sample,2,None),('参数类型非法',{'threshold':'abc'},sample,2,None),('缺失输入',{},data/'missing.png',2,None)]:
 out=base/n;request={'input':source.as_posix(),'output':out.as_posix(),**extra};r=call([exe],input=json.dumps(request,ensure_ascii=False),capture_output=True,text=True,timeout=20);ok=r.returncode==code
 if count is not None and ok:
  report=json.loads((out/'report.json').read_text());ok=report['count']==count and len(report['objects'])==count
  with Image.open(out/'overlay.png') as im:ok=ok and im.size==(400,300)
  for obj in report['objects']:ok=ok and obj['x']<=obj['cx']<obj['x']+obj['width'] and obj['y']<=obj['cy']<obj['y']+obj['height']
 elif code==2:ok=ok and not out.exists()
 record('视觉:'+n,ok,r.stdout+r.stderr)
out=base/'三件与噪点过滤';before={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in out.iterdir()};r=call([exe],input=json.dumps({'input':sample.as_posix(),'output':out.as_posix()}),capture_output=True,text=True,timeout=20);record('视觉:输出保护',r.returncode==2 and before=={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in out.iterdir()})
record('视觉:源图不变',all(hashlib.sha256(p.read_bytes()).hexdigest()==v for p,v in hashes.items()))
# 批量入口真实调用：合法图和坏图混合时必须继续并返回2，报告保留每图结果。
import sys,subprocess
batch=base/'batch-output';r=subprocess.run([sys.executable,str(ROOT/'tools/inspect-parts.py'),'--batch',str(data),'--output',str(batch)],capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=60)
summary=json.loads((batch/'batch-summary.json').read_text(encoding='utf-8')) if (batch/'batch-summary.json').exists() else []
record('视觉:批处理失败隔离',r.returncode==2 and len(summary)==3 and sum(x['passed'] for x in summary)==2,r.stdout+r.stderr)
bash=Path('D:/Git/bin/bash.exe');script=ROOT/'linux/projects/dataset-audit/reference.sh'
def posix(p):return '/'+p.drive[0].lower()+p.as_posix()[2:]
environment=dict(os.environ,MSYS_NO_PATHCONV='1')
empty=base/'empty';empty.mkdir()
for name,folder,args,code,expected in [('中文与空格',data,[],0,'images=3 others=0'),('空目录',empty,[],0,'images=0 others=0'),('坏路径',base/'missing',[],2,None)]:
 r=subprocess.run([str(bash),posix(script),posix(folder),*args],capture_output=True,env=environment,timeout=20)
 record('Linux:'+name,r.returncode==code and (expected.encode() in r.stdout if expected else True),r.stderr.decode(errors='replace'))
r=subprocess.run([str(bash),posix(script),posix(data),'--null'],capture_output=True,env=environment,timeout=20)
files=r.stdout.split(b'\0');record('Linux:NUL清单',r.returncode==0 and files[-1]==b'' and len(files[:-1])==3 and all(b'\n' not in f for f in files[:-1]))
record('Linux:源数据不变',all(hashlib.sha256(p.read_bytes()).hexdigest()==v for p,v in hashes.items()))
result={'directory':base.as_posix(),'passed':sum(x['passed'] for x in rows),'total':len(rows),'results':rows}
(ROOT/'guide/重点项目验收.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8');print(result['passed'],'/',result['total']);raise SystemExit(0 if all(x['passed'] for x in rows) else 1)
