"""WSL环境检查；C++开发链路另按需检查。"""
from pathlib import Path
import subprocess,json,sys
R=Path(__file__).resolve().parents[1];rows=[]
if sys.platform!='linux':raise SystemExit('请在WSL Ubuntu运行。')
def record(name,ok):rows.append({'name':name,'passed':bool(ok)})
for tool in ['bash','g++','gdb','cmake','ninja','shellcheck','python3']:
    p=subprocess.run(['bash','-c','command -v "$1"','tool-check',tool],capture_output=True,text=True);record('工具:'+tool,p.returncode==0)
workspace=json.loads((R/'workspaces/focus-wsl.code-workspace').read_text())
record('Linux工作区路径',all((R/'workspaces'/f['path']).resolve().is_dir() for f in workspace['folders']))
record('C++与Linux目录共存',any('/cpp/' in f['path'] for f in workspace['folders']) and any('/linux/' in f['path'] for f in workspace['folders']))
record('Linux默认后端',json.loads((R/'tools/runtime-settings.json').read_text())['shell_backend']=='wsl')
p=subprocess.run(['shellcheck',str(R/'linux/projects/dataset-audit/reference.sh')],capture_output=True,text=True);record('ShellCheck可用',p.returncode==0)
report={'scope':'WSL环境与Shell静态检查，不编译C++习题','passed':sum(r['passed'] for r in rows),'total':len(rows),'results':rows}
(R/'guide/WSL验收.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(report['passed'],'/',report['total']);raise SystemExit(0 if report['passed']==report['total'] else 1)
