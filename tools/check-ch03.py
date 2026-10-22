"""第3章已覆盖内容的参考验收；不修改个人状态。"""
from pathlib import Path
import subprocess,sys,json,importlib.util
R=Path(__file__).resolve().parents[1]
steps=[['wsl-book-check.py' if sys.platform=='linux' else 'check-book.py','--chapter','roberts-ch03'],['check-ch03-strings.py']]
for step in steps:
    subprocess.run([sys.executable,str(R/'tools'/step[0]),*step[1:]],cwd=R,check=True)
if sys.platform=='linux':
    spec=importlib.util.spec_from_file_location('native',R/'tools/wsl-study.py');native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native);build=native.build
else:
    from study import build
lab=build(R/'cpp/主教材/章节学习/第03章 字符串类string/讲解示例/文本转换/reference.cpp')
subprocess.run([str(lab)],check=True,timeout=10)
interactive=build(R/'cpp/主教材/章节学习/第03章 字符串类string/课后习题/第11题 忽略标点的句子回文/interactive.cpp')
for inp,want,code in [("Madam, I'm Adam.\nNot a palindrome.\n\nafter quit\n","true\nfalse\n",0),("\n","",0),("1a2\n","true\n",0),("中文\n","",2)]:
    run=subprocess.run([str(interactive)],input=inp,text=True,capture_output=True,timeout=10)
    assert run.returncode==code and run.stdout==want,(inp,run.stdout,run.stderr)
report={'backend':'wsl' if sys.platform=='linux' else 'windows','coverage':'原书1—20','fixed_cases_and_models':True,'transform_demo':True,'interactive_protocol_cases':4,'student_progress':'unchanged'}
(R/'guide'/('ch03-complete-'+report['backend']+'.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print('Chapter3 covered references, models, demo and interactive protocol passed.')
