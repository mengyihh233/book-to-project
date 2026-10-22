"""将当前第2章图形题输出保存为SVG；Windows可--open。"""
from pathlib import Path
import argparse,subprocess,sys,importlib.util,webbrowser
from graphics_model import parse
R=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('file',type=Path);p.add_argument('--input',type=Path);p.add_argument('--open',action='store_true');a=p.parse_args()
source=a.file.resolve()
if source.parent.parent!=R/'cpp/主教材/章节学习/第02章 函数与库/课后习题' or source.parent.name not in ['第16题','第17题','第18题'] or source.name not in ['reference.cpp','work.cpp']:p.error('请选择第2章16—18题的reference.cpp或work.cpp')
if sys.platform=='linux':
 spec=importlib.util.spec_from_file_location('native',R/'tools/wsl-study.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);build=module.build
else:
 from study import build
inp=(a.input or source.parent/'input.txt').read_text(encoding='utf-8-sig');parts=inp.split();w,h=map(int,parts) if parts else (640,400)
exe=build(source);run=subprocess.run([str(exe)],input=inp,text=True,capture_output=True,timeout=10)
if run.returncode:raise SystemExit(run.stderr)
parse(run.stdout,w,h)
out=source.parent/'运行结果'/(source.stem+'.svg');out.parent.mkdir(exist_ok=True);out.write_text(run.stdout,encoding='utf-8')
print(out)
if a.open:
 if sys.platform=='linux':print('请从Windows资源管理器打开D盘对应SVG文件。')
 else:webbrowser.open(out.as_uri())
