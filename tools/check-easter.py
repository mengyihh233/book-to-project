"""逐年对照独立公式与星期；只验收参考，不写学习进度。"""
from pathlib import Path
import subprocess,sys,json,datetime,importlib.util
ROOT=Path(__file__).resolve().parents[1]
if sys.platform=='linux':
 spec=importlib.util.spec_from_file_location('native',ROOT/'tools/wsl-study.py');native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native);build=native.build
else:
 from study import build
def expected(y):
 a=y%19;b=y//100;c=y%100;d=b//4;e=b%4;f=(b+8)//25;g=(b-f+1)//3
 h=(19*a+b-d-g+15)%30;i=c//4;k=c%4;l=(32+2*e+2*i-h-k)%7;m=(a+11*h+22*l)//451
 return (h+l-7*m+114)//31,(h+l-7*m+114)%31+1
base=ROOT/'cpp/主教材/章节学习/第02章 函数与库/课后习题/第08题'
exe=build(base/'tests.cpp');p=subprocess.run([str(exe)],text=True,capture_output=True,timeout=15,check=True)
counts={'B':0,'G':0};seen=set()
for line in p.stdout.splitlines():
 kind,year,month,day=line.split();year=int(year);day=int(day)
 assert kind in counts and (kind,year) not in seen;seen.add((kind,year))
 actual=(3 if month=='March' else 4,day);assert month in ['March','April']
 assert actual==expected(year),(kind,year,actual,expected(year))
 assert (3,22)<=actual<=(4,25) and datetime.date(year,*actual).weekday()==6
 counts[kind]+=1
assert counts=={'B':200,'G':2517},counts
assert expected(1818)==(3,22) and expected(1943)==(4,25)
extension=build(base/'extension.cpp');io=0
for text,output,code in [('1583\n','April 10',0),('1818\n','March 22',0),('1943\n','April 25',0),('2010\n','April 4',0),('2026\n','April 5',0),('4099\n','April 19',0),('1582\n','',2),('4100\n','',2),('2026 extra\n','',2),('abc\n','',2),('','',2)]:
 p=subprocess.run([str(extension)],input=text,text=True,capture_output=True,timeout=10)
 assert p.returncode==code and p.stdout.strip()==output,(text,p.stdout,p.stderr);io+=1
report={'backend':'wsl' if sys.platform=='linux' else 'windows','original_years':counts['B'],'extension_years':counts['G'],'extension_io_cases':io,'independent_formula':True,'date_bounds_and_sunday':True,'invalid_reference_unchanged':True}
(ROOT/'guide'/('easter-verification-'+report['backend']+'.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(report,ensure_ascii=False))
