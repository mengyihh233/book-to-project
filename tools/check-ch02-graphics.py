"""独立验收第2章16—18题的图形；不改变学习进度。"""
import argparse,json,subprocess,sys,importlib.util
from pathlib import Path
from graphics_model import verify
R=Path(__file__).resolve().parents[1]
if sys.platform=='linux':
 spec=importlib.util.spec_from_file_location('native',R/'tools/wsl-study.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);build=module.build
else:
 from study import build,call
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--file',type=Path);a=p.parse_args()
files=[a.file.resolve()] if a.file else [R/f'cpp/主教材/章节学习/第02章 函数与库/课后习题/第{n}题/reference.cpp' for n in [16,17,18]]
results=[]
for source in files:
 if source.parent.parent!=R/'cpp/主教材/章节学习/第02章 函数与库/课后习题' or source.parent.name not in ['第16题','第17题','第18题'] or source.name not in ['reference.cpp','work.cpp']:p.error('请选择第2章16—18题的reference.cpp或work.cpp')
 ex=int(source.parent.name[1:-1]);exe=build(source)
 for inp,w,h in [('',640,400),('640 400\n',640,400),('400 640\n',400,640),('800 800\n',800,800),('200 200\n',200,200)]:
  run=subprocess.run([str(exe)],input=inp,text=True,capture_output=True,timeout=10)
  if run.returncode:raise RuntimeError(run.stderr)
  count=verify(run.stdout,ex,w,h)
  results.append({'exercise':ex,'size':[w,h],'sampled_points':count,'passed':True})
 for bad in ['199 400\n','400 1601\n','foo\n','640\n','640 400 extra\n','640 400.0\n']:
  run=subprocess.run([str(exe)],input=bad,text=True,capture_output=True,timeout=10)
  if run.returncode!=2 or run.stdout.strip():raise ValueError(f'错误输入未正确拒绝：{bad!r}')
  results.append({'exercise':ex,'invalid_input':bad,'passed':True})
report={'backend':'wsl' if sys.platform=='linux' else 'windows','passed':len(results),'total':len(results),'sampled_points':sum(r.get('sampled_points',0) for r in results),'scope':'basic SVG fill and invalid input, not anti-aliasing or full visual proof','results':results}
if not a.file:(R/'guide'/('ch02-graphics-'+report['backend']+'.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in report.items() if k!='results'},ensure_ascii=False))
