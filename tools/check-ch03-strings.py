"""参考函数契约与独立随机ASCII模型，不修改学习状态。"""
from pathlib import Path
import subprocess,json,sys,random,importlib.util
from strings_oracle import expected
R=Path(__file__).resolve().parents[1]
if sys.platform=='linux':
 spec=importlib.util.spec_from_file_location('native',R/'tools/wsl-study.py');native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native);build=native.build
else:
 from study import build
rand=random.Random(20261019);checks=0;results=[]
for n in range(1,21):
 folder=R/f'cpp/主教材/章节学习/第03章 字符串类string/课后习题/第{n:02}题'
 contracts=build(folder/'tests.cpp');subprocess.run([str(contracts)],check=True,capture_output=True,timeout=15)
 exe=build(folder/'reference.cpp')
 for i in range(80):
  s=''.join(rand.choices('abCDxyz019-!? \t',k=rand.randrange(50)))
  parts=[s]
  if n in [1,7,8]:parts.append(''.join(rand.choices('abCDxyz019-!? \t',k=rand.randrange(12))))
  if n==3:parts.extend([str(rand.randrange(len(s)+1)), 'ALL' if i%5==0 else str(rand.randrange(len(s)+20))])
  if n==10:
   mode='char' if i%2 else 'string';needle=''.join(rand.choices('abCD ',k=1 if mode=='char' else rand.randrange(1,5)));replacement=''.join(rand.choices('abCD ',k=1 if mode=='char' else rand.randrange(8)));parts=[mode,s,needle,replacement]
  if n==12:parts=[''.join(rand.choices('abcdefghijklmnopqrstuvwxyz',k=rand.randrange(1,25)))]
  if n==13:parts=[str(rand.randrange(2**63))]
  if n==14:parts=[''.join(rand.choices('0123456789',k=rand.randrange(1,61)))]
  if n==16:parts=[''.join(rand.choices('abcdefghijklmnopqrstuvwxyz',k=rand.randrange(1,30)))]
  if n==17:parts=[s,str(rand.randrange(-2**63,2**63))]
  if n in [18,19]:
   key=''.join(rand.sample('ABCDEFGHIJKLMNOPQRSTUVWXYZ',26));parts=[key,s] if n==18 else [key]
  if n==20:parts=[''.join(rand.choices('ACGTacgt',k=rand.randrange(9))),''.join(rand.choices('ACGTacgt',k=rand.randrange(40))),str(rand.randrange(45))]
  text='\n'.join(parts)+'\n';run=subprocess.run([str(exe)],input=text,text=True,capture_output=True,timeout=10)
  actual=run.stdout.removesuffix('\n');want=expected(n,parts)
  assert run.returncode==0 and actual==want,(n,parts,repr(actual),repr(want),run.stderr)
  # 独立Python字符串模型对照；接口性质另由tests.cpp检查。
  checks+=1
 results.append({'exercise':n,'random_ascii_cases':80,'contracts_passed':True})
report={'backend':'wsl' if sys.platform=='linux' else 'windows','independent_cases':checks,'contract_programs':len(results),'fixed_seed':20261019,'output_whitespace_preserved':True,'results':results}
(R/'guide'/('ch03-strings-'+report['backend']+'.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in report.items() if k!='results'},ensure_ascii=False))
