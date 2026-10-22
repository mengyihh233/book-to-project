"""第2章参考实现总验收：文本、图形、随机模型、日期交叉检查。"""
from pathlib import Path
import subprocess,sys,json
R=Path(__file__).resolve().parents[1]
steps=[['wsl-book-check.py' if sys.platform=='linux' else 'check-book.py','--chapter','roberts-ch02'],['check-ch02-graphics.py'],['check-random-exercises.py'],['check-easter.py']]
for step in steps:
 print('Checking: '+' '.join(step),flush=True)
 run=subprocess.run([sys.executable,str(R/'tools'/step[0]),*step[1:]],cwd=R)
 if run.returncode:raise SystemExit(run.returncode)
report={'backend':'wsl' if sys.platform=='linux' else 'windows','steps_passed':len(steps),'total_steps':len(steps),'scope':'参考实现验收，不修改个人作答或完成状态','steps':steps}
(R/'guide'/('ch02-complete-'+report['backend']+'.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print('第2章四组参考验收全部通过；学习进度未修改。')
