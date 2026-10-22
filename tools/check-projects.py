from pathlib import Path
import json,hashlib
from study import ROOT,build,call,linux_path,bash_command,GIT_BASH,bash_path,use_git_bash,wsl_distribution
from project_fixtures import prepare
from PIL import Image
rows=[]
def record(name,passed,details=''):
    rows.append({'name':name,'passed':bool(passed),'details':details})
    print(name,'通过' if passed else '失败',flush=True)

# Linux验收在独立输出目录创建测试数据，不修改学习者输入。
fixtures=ROOT/'linux/projects/score-report/output/verification'
fixtures.mkdir(parents=True,exist_ok=True)
script=ROOT/'linux/projects/score-report/reference.sh'
cases=[
    ('正常含空格路径','name,score\nAlice,80\nBob,59.5\nCarol,90\n',0,'学生人数：3\n平均分：76.50\n最低分：59.50\n最高分：90.00\n及格人数：2'),
    ('只有表头','name,score\n',0,'学生人数：0\n暂无成绩'),
    ('CRLF与空行','name,score\r\n\r\nA,100\r\n',0,'学生人数：1\n平均分：100.00\n最低分：100.00\n最高分：100.00\n及格人数：1'),
    ('重复姓名','name,score\nA,80\nA,90\n',2,None),
    ('成绩超范围','name,score\nA,101\n',2,None),
    ('非法成绩','name,score\nA,NaN\n',2,None),
    ('空文件','',2,None),
    ('错误表头','student,score\nA,80\n',2,None),
    ('多余字段','name,score\nA,80,90\n',2,None),
]
for i,(label,text,code,expected) in enumerate(cases):
    p=fixtures/f'{i:02d} case.csv';p.write_bytes(text.encode('utf-8'))
    before=hashlib.sha256(p.read_bytes()).hexdigest()
    r=call(bash_command(script,p),capture_output=True,text=True,timeout=15)
    ok=r.returncode==code and (r.stdout.strip()==expected if expected is not None else not r.stdout)
    ok=ok and hashlib.sha256(p.read_bytes()).hexdigest()==before
    record('Linux：'+label,ok,r.stdout+r.stderr)
lint_cmd=[GIT_BASH,'-n',bash_path(script)] if use_git_bash() else ['wsl.exe','-d',wsl_distribution(),'--','shellcheck',linux_path(script)]
r=call(lint_cmd,capture_output=True,text=True,timeout=15)
record('Linux：Bash语法检查（非ShellCheck）' if use_git_bash() else 'Linux：ShellCheck',r.returncode==0,r.stdout+r.stderr)

sample=prepare();exe=build(ROOT/'opencv/projects/image-pipeline/main.cpp')
out=ROOT/'opencv/projects/image-pipeline/output/verification';out.mkdir(parents=True,exist_ok=True)
target=out/'中文 结果.png'
before=hashlib.sha256(sample.read_bytes()).hexdigest()
r=call([exe,'--input',sample,'--output',target,'--overwrite'],capture_output=True,text=True,timeout=20)
ok=r.returncode==0
if ok:
    with Image.open(target) as image:ok=image.size==(160,120) and image.mode=='L' and image.getextrema()[1]>0
record('OpenCV：中文路径与有效边缘输出',ok,r.stdout+r.stderr)
saved=hashlib.sha256(target.read_bytes()).hexdigest() if target.exists() else ''
r=call([exe,'--input',sample,'--output',target],capture_output=True,text=True,timeout=20)
record('OpenCV：已有输出保护',r.returncode==2 and hashlib.sha256(target.read_bytes()).hexdigest()==saved,r.stderr)
r=call([exe,'--input',sample,'--output',sample,'--overwrite'],capture_output=True,text=True,timeout=20)
record('OpenCV：源图保护',r.returncode==2 and hashlib.sha256(sample.read_bytes()).hexdigest()==before,r.stderr)
bad=out/'not-image.txt';bad.write_text('不是图片',encoding='utf-8')
for name,args in [
    ('输入缺失',['--input',out/'absent.png']),
    ('图片解码失败',['--input',bad]),
    ('偶数高斯核',['--input',sample,'--blur','4']),
    ('高低阈值倒置',['--input',sample,'--low','150','--high','50']),
    ('参数尾随字符',['--input',sample,'--low','5abc']),
    ('缺少参数值',['--input']),
]:
    if name!='缺少参数值':args+=['--output',target,'--overwrite']
    r=call([exe,*args],capture_output=True,text=True,timeout=20)
    record('OpenCV：'+name,r.returncode==2,r.stderr)
report={'passed':sum(r['passed'] for r in rows),'total':len(rows),'results':rows}
(ROOT/'guide/综合项目验收.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(f'{report["passed"]}/{report["total"]}项通过。')
raise SystemExit(0 if report['passed']==report['total'] else 1)
