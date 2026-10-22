"""参考实现的独立模型与状态性质检查；不修改学习进度。"""
from pathlib import Path
import argparse, json, subprocess, math, sys, importlib.util
from random_oracle import MT, oracle
parser=argparse.ArgumentParser();parser.add_argument('--wsl',action='store_true');args=parser.parse_args()
ROOT=Path(__file__).resolve().parent.parent
native_linux=sys.platform=='linux'
if native_linux:
    spec=importlib.util.spec_from_file_location('wsl_study',ROOT/'tools/wsl-study.py')
    native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native)
else:
    from study import build, wsl_distribution
results=[]
for n in range(12,16):
    source=ROOT/f'cpp/主教材/章节学习/第02章 函数与库/课后习题/第{n}题/reference.cpp'
    if native_linux:
        exe=native.build(source)
        def run(inp):
            p=subprocess.run([str(exe)],input=inp,text=True,capture_output=True,timeout=10,check=True)
            return p.stdout.strip()
    elif args.wsl:
        # 与日常 WSL 构建入口一致，避免另配编译器。
        relative='仓库根目录/'+source.relative_to(ROOT).as_posix()
        built=subprocess.run(['wsl.exe','-d',wsl_distribution(),'--','python3','仓库根目录/tools/wsl-study.py','build',relative],text=True,capture_output=True,timeout=60,check=True)
        executable=built.stdout.strip()
        def run(inp):
            p=subprocess.run(['wsl.exe','-d',wsl_distribution(),'--',executable],input=inp,text=True,capture_output=True,timeout=10)
            if p.returncode:raise RuntimeError(p.stderr+p.stdout)
            return p.stdout.strip()
    else:
        exe=build(source)
        def run(inp):
            p=subprocess.run([str(exe)],input=inp,text=True,capture_output=True,timeout=10)
            if p.returncode:raise RuntimeError(p.stderr)
            return p.stdout.strip()
    for seed in [0,1,2,42,5489,2026,65535,4294967295]:
        count=1000
        inp=f'{count} {seed}\n' if n==12 else f'{seed}\n'
        out=run(inp)
        assert out==oracle(n,seed,count),(n,seed,'independent model mismatch',out)
        assert run(inp)==out,(n,seed,'not reproducible')
        if n==12:assert 0<float(out)<1
        if n==13:
            pairs=[list(map(int,line.split())) for line in out.splitlines()]
            assert pairs[0]==[0,10000] and pairs[-1][1]==0
            assert all(b[0]==a[0]+1 and 0<=b[1]<=a[1] for a,b in zip(pairs,pairs[1:]))
        if n==14:
            hits,pi=out.split();assert 0<=int(hits)<=10000
            assert abs(float(pi)-4*int(hits)/10000)<1e-9
            # 固定这些种子的宽松回归界限，不是每次随机试验的必然保证。
            assert abs(float(pi)-math.pi)<0.15
        if n==15:
            lines=out.splitlines();coins=lines[:-1]
            assert lines[-1]==f'TOTAL {len(coins)}'
            assert set(coins)<={'HEADS','TAILS'} and coins[-3:]==['HEADS']*3
            assert not any(coins[i:i+3]==['HEADS']*3 for i in range(len(coins)-3))
        results.append({'exercise':n,'seed':seed,'passed':True})
report={'backend':'wsl' if args.wsl or native_linux else 'windows','passed':len(results),'total':len(results),'checks':'independent MT model, deterministic repeat, simulation invariants','results':results}
target=ROOT/'guide'/('random-verification-wsl.json' if args.wsl or native_linux else 'random-verification-windows.json')
target.write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in report.items() if k!='results'},ensure_ascii=False))
