"""Ubuntu内检查Roberts原书样例；支持当前work.cpp，不修改学习状态。"""
import argparse,importlib.util,json,math,subprocess
from answer_compare import matches
from file_cases import case_directory,verify_case_files
from scaffold_state import source_template_reason
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('native_study',ROOT/'tools/wsl-study.py');native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native)
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--work',type=Path);p.add_argument('--chapter');a=p.parse_args()
items=[x for x in json.loads((ROOT/'tools/book-tests.json').read_text(encoding='utf-8')) if x['id'].startswith('roberts-')]
if a.chapter:items=[x for x in items if x['id'].startswith(a.chapter+'-')]
if a.work:items=[x for x in items if (ROOT/x['source']).parent.resolve()==a.work.parent.resolve()]
elif not a.chapter:items=[x for x in items if x['id'].startswith('roberts-ch01-')]
chapter=a.chapter or (items[0]['id'].rsplit('-',1)[0] if items else 'unknown')
if not items:p.error('没有匹配的Roberts原书题目；请选择已登记的题目作答位')
passed=0;total=0;pending_total=0
for item in items:
 source=native.source(a.work if a.work else ROOT/item['source'])
 pending=source_template_reason(ROOT,source)
 if pending:
  print(str(item.get('id',source.name))+' 尚未开始作答：'+pending+'；不计入通过，也不算样例失败。',flush=True);pending_total+=1;continue
 exe=native.build(source)
 for i,(inp,expected) in enumerate(item['cases']):
  with case_directory(item,source.parent) as folder:
   r=subprocess.run([str(exe)],input=inp,capture_output=True,text=True,encoding="utf-8",timeout=10,cwd=folder)
   files_ok,file_errors=verify_case_files(item,i,folder)
  actual=r.stdout if item.get('preserve_all_output') else (r.stdout.removesuffix('\n') if item.get('preserve_output') else r.stdout.strip());match=matches(actual,expected,item)
  ok=match and files_ok and r.returncode==item.get('expected_exit_codes',[0]*len(item['cases']))[i];passed+=ok;total+=1;print('样例'+str(i+1)+'：'+('通过' if ok else '未通过'),flush=True)
  if file_errors:print('文件检查：',file_errors)
  if not ok:print('期望',repr(expected),'实际',repr(actual),'退出码',r.returncode)
print(f'{passed}/{total} 通过；样例不是完整正确性的证明。')
if pending_total:print('其中 '+str(pending_total)+' 题尚未开始作答，未计入上面的样例统计。',flush=True)
if not a.work:(ROOT/'guide'/('WSL-Roberts原书验收.json' if chapter=='roberts-ch01' else 'WSL-Roberts-'+chapter+'验收.json')).write_text(json.dumps({'passed':passed,'total':total,'pending':pending_total,'chapter':chapter,'backend':'Ubuntu GCC'},ensure_ascii=False,indent=2),encoding='utf-8')
if pending_total and not total:raise SystemExit(3)
raise SystemExit(0 if passed==total else 1)
