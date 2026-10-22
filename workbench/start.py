"""Start the shared learning workbench and optional browser VS Code locally."""
import argparse,subprocess,sys,time,webbrowser
from pathlib import Path
from urllib.request import build_opener,ProxyHandler
HERE=Path(__file__).resolve().parent;ROOT=HERE.parent
parser=argparse.ArgumentParser();parser.add_argument('--no-browser',action='store_true');parser.add_argument('--remote',action='store_true');args=parser.parse_args()
opener=build_opener(ProxyHandler({}))
def status(port,path='/'):
 try:
  with opener.open(f'http://127.0.0.1:{port}{path}',timeout=1) as r:return r.status
 except Exception:return None
def launch(command,logname):
 with (HERE/logname).open('a',encoding='utf-8') as log:
  subprocess.Popen(command,cwd=ROOT,stdout=log,stderr=log,creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0))
if status(18765,'/api/health')!=200:
 launch([sys.executable,str(HERE/'server.py')],'server.log')
 for _ in range(40):
  if status(18765,'/api/health')==200:break
  time.sleep(.15)
if args.remote and status(18766) not in (200,202):
 executable=Path('D:/Microsoft VS Code/bin/code-tunnel.exe')
 if executable.exists():launch([str(executable),'serve-web','--host','127.0.0.1','--port','18766','--without-connection-token','--disable-telemetry','--server-data-dir',str(ROOT/'.remote-vscode'),'--cli-data-dir',str(ROOT/'.remote-vscode-cli'),'--default-folder',str(ROOT)],'editor.log')
if status(18765,'/api/health')!=200:raise RuntimeError('工作台未启动，请查看workbench/server.log；不要关闭不明端口进程。')
if not args.no_browser:webbrowser.open('http://127.0.0.1:18765')
