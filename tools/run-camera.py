"""相机实验：正常窗口、纯数学测试或隐藏GPU验收。"""
import argparse,json,sys
from pathlib import Path
import study
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');p.add_argument('--math',action='store_true');p.add_argument('--work',action='store_true');args=p.parse_args()
folder=study.ROOT/'opengl/projects/camera-lab';source=folder/('work/main.cpp' if args.work else 'reference.cpp')
out=study.build(source)
if args.work and (args.check or args.math):p.error('自己的作答请独立设计验收；参考验收使用 --check')
if not args.check:sys.exit(study.call([out,*(['--math'] if args.math else [])],cwd=folder).returncode)
rows=[]
for label,argv in [('数学','--math'),('GPU双视角','--smoke'),('错误参数','--unknown')]:
 r=study.call([out,argv],cwd=folder,capture_output=True,text=True,timeout=30)
 ok=r.returncode==(2 if label=='错误参数' else 0)
 rows.append(dict(check=label,passed=ok,output=r.stdout+r.stderr));print(label,'PASS' if ok else 'FAIL',flush=True)
if all(r['passed'] for r in rows):
 from PIL import Image
 for name in ('view-a','view-b'):
  with Image.open(folder/'output'/f'{name}.ppm') as im:im.save(folder/'output'/f'{name}.png')
(study.ROOT/'guide/相机实验验收.json').write_text(json.dumps({'source':source.relative_to(study.ROOT).as_posix(),'results':rows},ensure_ascii=False,indent=2),encoding='utf-8')
sys.exit(0 if all(r['passed'] for r in rows) else 1)
