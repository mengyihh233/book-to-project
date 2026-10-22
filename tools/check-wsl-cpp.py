"""按需检查Linux C++开发链路，不批量重跑教材。"""
from pathlib import Path
import sys,subprocess,json,importlib.util
R=Path(__file__).resolve().parents[1]
if sys.platform!='linux':raise SystemExit('请在WSL Ubuntu运行。')
spec=importlib.util.spec_from_file_location('native',R/'tools/wsl-study.py');native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native)
rows=[]
def record(name,ok):
 rows.append({'name':name,'passed':bool(ok)})
 if not ok:raise RuntimeError(name+' failed')
exe=native.build(R/'cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/reference.cpp',active=True)
record('Linux ELF',exe.read_bytes()[:4]==b'\x7fELF')
p=subprocess.run([str(exe)],input='IBM 9000\n-1\n',text=True,capture_output=True,timeout=10);record('C++编译和文件式stdin',p.returncode==0 and p.stdout=='HAL 9000\n')
p=subprocess.run(['gdb','--batch','-ex','break main','-ex','run','--args',str(exe)],text=True,capture_output=True,timeout=30);record('GDB main断点',p.returncode==0 and 'Breakpoint 1,' in p.stdout)
exe=native.build(R/'cpp/主教材/章节学习/第02章 函数与库/课后习题/第10题 组合数学库/reference.cpp')
p=subprocess.run([str(exe)],input='C 6 2\n',text=True,capture_output=True,timeout=10);record('多文件库链接',p.returncode==0 and p.stdout.strip()=='15')
w=json.loads((R/'workspaces/focus-wsl.code-workspace').read_text());record('工作区路径',all((R/'workspaces'/f['path']).resolve().is_dir() for f in w['folders']))
launch=w['launch']['configurations'][0];record('调试任务匹配',any(t['label']==launch['preLaunchTask'] for t in w['tasks']['tasks']) and launch['program']=='${env:HOME}/.cache/book-learning/active-program')
extensions=[Path.home()/'.vscode/extensions',Path.home()/'.vscode-server/extensions']
record('C++扩展（原生或远程）',any(p.is_dir() for folder in extensions for p in folder.glob('ms-vscode.cpptools-*')))
report={'scope':'Linux C++开发烟雾检查；非整本教材重验','passed':len(rows),'total':len(rows),'results':rows,'ui_f5':'配置与命令行GDB已验证，未自动操作VS Code F5界面'}
(R/'guide/WSL-C++开发检查.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(report,ensure_ascii=False))
