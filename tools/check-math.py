"""微积分选做程序检查；参考验收不修改个人学习进度。"""
from pathlib import Path
import argparse,importlib.util,json,math,os,subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
def cases(project):
 if project=='ode-euler':
  valid=[]
  for n,t,y,k in [(1,1,1,1),(2,1,1,1),(4,1,1,1),(20,4,1,1),(50,2,3,-1),(10,0,-2,3),(30,1,0,1),(10000,1,1,1),(1,20,1,5)]:
   v=y*(1+k*t/n)**n;e=y*math.exp(k*t);valid.append((f'{n} {t} {y} {k}\n',{'euler':v,'exact':e,'error':v-e}))
  bad=['','0 1 1 1\n','10001 1 1 1\n','2 -1 1 1\n','2 21 1 1\n','2 1 101 1\n','2 1 1 6\n','2 nan 1 1\n','2 1 1 1 extra\n','2 1 1\n']
 elif project=='polar-area':
  valid=[]
  for kind,a,n in [('circle',2,24),('circle',0,1),('cardioid',2,1000),('rose3',2,1000),('cardioid',1,1),('rose3',1,1),('rose3',3,24),('circle',100,10000)]:
   end=math.pi if kind=='rose3' else 2*math.pi
   def radius(t):return a if kind=='circle' else a*(1+math.cos(t)) if kind=='cardioid' else a*math.sin(3*t)
   area=math.fsum(radius((i+.5)*end/n)**2 for i in range(n))*end/(2*n)
   exact=math.pi*a*a*(1 if kind=='circle' else 1.5 if kind=='cardioid' else .25)
   valid.append((f'{kind} {a} {n}\n',{'area':area,'exact':exact,'error':area-exact}))
  bad=['','unknown 2 10\n','circle -1 10\n','circle 101 10\n','circle 1 0\n','circle 1 1000001\n','rose3 nan 10\n','circle 1 2 extra\n']
 elif project=='sequence-sums':
  valid=[(f'{n}\n',{'geometric':1.5*(1-3.0**(-n)),'telescoping':1-1/(n+1)}) for n in [0,1,2,8,20,1000,100000]]
  bad=['','-1\n','100001\n','1.5\n','8 extra\n','nan\n']
 elif project=='opencv':
  valid=[(f'{n}\n',{'du':2,'dv':3,'magnitude':math.sqrt(13)}) for n in [3,5,101]]
  bad=['','1\n','4\n','103\n','5 extra\n']
 else:raise ValueError('unknown project')
 return [(x,y,0) for x,y in valid]+[(x,{},2) for x in bad]
def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--project',choices=['ode-euler','polar-area','sequence-sums','opencv']);parser.add_argument('--work',action='store_true',help='检查独立work.cpp，不保存参考验收报告');a=parser.parse_args()
 if a.work and not a.project:parser.error('--work需要指定--project')
 projects=[a.project] if a.project else ['ode-euler','polar-area','sequence-sums','opencv'];results=[]
 module_file=ROOT/'tools'/('wsl-study.py' if sys.platform=='linux' else 'study.py');spec=importlib.util.spec_from_file_location('math_study_runtime',module_file);runtime=importlib.util.module_from_spec(spec);spec.loader.exec_module(runtime)
 for project in projects:
  source=ROOT/'math/projects'/project/('work.cpp' if a.work else 'reference.cpp');exe=runtime.build(source);passed=0;failures=[]
  for i,(text,expected,code) in enumerate(cases(project),1):
   if sys.platform=='linux':r=subprocess.run([str(exe)],input=text,text=True,capture_output=True,timeout=10)
   else:r=runtime.call([exe],input=text,text=True,capture_output=True,timeout=10)
   ok=r.returncode==code
   if code==2:ok=ok and not r.stdout
   else:
    try:
     parts=r.stdout.split();actual=dict(p.split('=',1) for p in parts);ok=ok and len(parts)==len(expected) and set(actual)==set(expected)
     ok=ok and all(math.isfinite(float(actual[k])) and math.isclose(float(actual[k]),v,rel_tol=1e-9,abs_tol=1e-9) for k,v in expected.items())
    except (ValueError,KeyError,OverflowError):ok=False
   if ok:passed+=1
   else:failures.append({'case':i,'exit':r.returncode,'stdout':r.stdout[:300],'stderr':r.stderr[:300]})
  results.append({'project':project,'passed':passed,'total':len(cases(project)),'failures':failures});print(f'{project}: {passed}/{len(cases(project))}')
 report={'platform':sys.platform,'reference':not a.work,'passed':sum(x['passed'] for x in results),'total':sum(x['total'] for x in results),'projects':results,'note':'只检查选做程序，不自动批改手写证明、不改变学习进度。'}
 if not a.work:(ROOT/'guide'/('math-verification-wsl.json' if sys.platform=='linux' else 'math-verification.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
 return 0 if report['passed']==report['total'] else 1
if __name__=='__main__':
 try:raise SystemExit(main())
 except (OSError,ValueError,subprocess.SubprocessError) as e:print('数学检查失败：',e,file=sys.stderr);raise SystemExit(2)
