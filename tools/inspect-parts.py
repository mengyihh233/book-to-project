"""机器视觉项目入口：单图/批处理与JSON参数复用，所有输出保留在D盘学习区。"""
import argparse,json,time
from pathlib import Path
from study import ROOT,build,call
p=argparse.ArgumentParser(description=__doc__)
group=p.add_mutually_exclusive_group(required=True);group.add_argument('--input',type=Path);group.add_argument('--batch',type=Path);group.add_argument('--demo',action='store_true')
p.add_argument('--output',type=Path);p.add_argument('--config',type=Path);p.add_argument('--threshold',type=int);p.add_argument('--min-area',type=float);p.add_argument('--max-area',type=float);p.add_argument('--light-objects',action='store_true');a=p.parse_args()
folder=ROOT/'opencv/projects/parts-inspector'
cfg={'threshold':100,'min_area':200,'max_area':100000,'invert':1}
if a.config:
 user=json.loads(a.config.read_text(encoding='utf-8-sig'))
 if not isinstance(user,dict) or set(user)-set(cfg):p.error('配置文件只允许 threshold/min_area/max_area/invert')
 cfg.update(user)
for key,value in [('threshold',a.threshold),('min_area',a.min_area),('max_area',a.max_area)]:
 if value is not None:cfg[key]=value
if a.light_objects:cfg['invert']=0
if a.demo:
 from PIL import Image,ImageDraw
 source=folder/'data/demo.png';source.parent.mkdir(parents=True,exist_ok=True)
 if not source.exists():
  image=Image.new('RGB',(640,400),'white');draw=ImageDraw.Draw(image);draw.ellipse((60,90,180,210),fill=(35,35,35));draw.rectangle((280,100,430,240),fill=(30,30,30));draw.ellipse((470,180,570,280),fill=(45,45,45));draw.rectangle((10,10,13,13),fill='black');image.save(source)
 inputs=[source]
elif a.batch:
 if not a.batch.is_dir():p.error('批处理输入不是目录')
 inputs=sorted((f for f in a.batch.iterdir() if f.is_file() and not f.is_symlink() and f.suffix.lower() in ('.png','.jpg','.jpeg','.bmp')),key=lambda p:p.name)
 if not inputs:p.error('没有可处理的图像')
else:inputs=[a.input]
out=(a.output or folder/'output'/f'run-{time.time_ns()}').resolve()
if not out.is_relative_to(ROOT):p.error('输出需位于 仓库根目录 内')
if out.exists():p.error('输出目录已存在；请指定新的目录，避免覆盖')
if a.batch and (out==a.batch.resolve() or out.is_relative_to(a.batch.resolve())):p.error('批处理输出目录不能位于输入目录中')
exe=build(folder/'reference.cpp');results=[]
for i,source in enumerate(inputs):
 target=out/f'{i:04}-{source.stem}' if a.batch else out
 request={**cfg,'input':source.resolve().as_posix(),'output':target.as_posix()}
 r=call([exe],input=json.dumps(request,ensure_ascii=False,allow_nan=False),capture_output=True,text=True,timeout=30)
 results.append({'input':str(source),'output':str(target),'passed':r.returncode==0,'details':r.stdout+r.stderr});print(source.name, 'PASS' if r.returncode==0 else 'FAIL',r.stdout+r.stderr)
if a.batch:
 out.mkdir(parents=True,exist_ok=True);(out/'batch-summary.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
print('输出目录：',out)
raise SystemExit(0 if all(x['passed'] for x in results) else 2)
