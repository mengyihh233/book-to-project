"""Read-only connectivity checks for the local learning workstation."""
import argparse,json,subprocess,sys
from pathlib import Path
from urllib.request import build_opener,ProxyHandler
ROOT=Path(__file__).resolve().parents[1]
def diagnose():
    opener=build_opener(ProxyHandler({}));results=[]
    def add(name,status,detail):results.append(dict(name=name,status=status,detail=detail))
    try:
        with opener.open('http://127.0.0.1:18765/api/health',timeout=2) as r:data=json.load(r)
        add('学习工作台','正常' if data.get('app')=='book-learning-workbench' else '需检查','本机18765；页面必须属于学习工作台')
    except Exception:add('学习工作台','未确认','先运行workbench/start.py --remote；本检查不启动或停止服务')
    try:
        with opener.open('http://127.0.0.1:18766/',timeout=2) as r:status=r.status
        add('网页版VS Code','正常' if status==200 else '准备中',f'本机18766返回{status}；首次下载时稍后刷新')
    except Exception:add('网页版VS Code','未确认','查看workbench/editor.log；不据此认定Tailscale断开')
    ts=Path('C:/Program Files/Tailscale/tailscale.exe')
    try:
        proc=subprocess.run([str(ts),'status','--json'],capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=5,check=True);data=json.loads(proc.stdout)
        peers=[p.get('HostName','设备') for p in (data.get('Peer') or {}).values() if p.get('Online')]
        add('Tailscale','正常' if data.get('BackendState')=='Running' else '需检查','电脑：'+(data.get('Self') or {}).get('HostName','未知')+'；在线对端：'+('、'.join(peers) or '暂未看到在线设备'))
        proc=subprocess.run([str(ts),'serve','status','--json'],capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=5,check=True);serve=json.loads(proc.stdout)
        proxies=[v.get('Proxy','') for site in serve.get('Web',{}).values() for v in site.get('Handlers',{}).values()]
        expected={'http://127.0.0.1:18765','http://127.0.0.1:18766'}
        add('私有入口转发','正常' if expected.issubset(proxies) else '需检查','应同时转发工作台18765与编辑器18766；本检查不改Serve配置')
    except (OSError,ValueError,subprocess.SubprocessError):add('Tailscale读取','未确认','可能权限或服务状态未就绪。请在本人的Windows终端运行tailscale status；读取失败不能单独证明服务已停止')
    add('共享源码','正常' if (ROOT/'cpp/主教材').is_dir() else '需检查',str(ROOT)+'；WSL对应仓库根目录')
    return results
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--json',action='store_true');args=parser.parse_args()
    if hasattr(sys.stdout,'reconfigure'):sys.stdout.reconfigure(encoding='utf-8')
    results=diagnose()
    if args.json:print(json.dumps(results,ensure_ascii=False,indent=2))
    else:
        print('联合学习只读检查（不修改配置、代码或进度）\n')
        for r in results:print('['+r['status']+'] '+r['name']+'：'+r['detail'])
    return 0 if all(r['status']=='正常' for r in results) else 1
if __name__=='__main__':raise SystemExit(main())
