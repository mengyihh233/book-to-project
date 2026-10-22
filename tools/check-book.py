from study import ROOT,build,call
import json,math,argparse
from answer_compare import matches
from file_cases import case_directory,verify_case_files
parser=argparse.ArgumentParser();parser.add_argument('--chapter',help='例如 ppp-ch05，仅验收指定章节');args=parser.parse_args()
results=[]
for item in json.loads((ROOT/'tools/book-tests.json').read_text(encoding='utf-8')):
    if args.chapter and not item['id'].startswith(args.chapter+'-'):continue
    exe=build(ROOT/item['source'])
    for case_index,(inp,expected) in enumerate(item['cases']):
        with case_directory(item) as folder:
            p=call([exe],input=inp,capture_output=True,text=True,timeout=10,cwd=folder)
            files_ok,file_errors=verify_case_files(item,case_index,folder)
        actual=p.stdout if item.get('preserve_all_output') else (p.stdout.removesuffix('\n') if item.get('preserve_output') else p.stdout.strip())
        if item.get('last_line'):actual=actual.splitlines()[-1] if actual else ''
        match=matches(actual,expected,item)
        expected_exit=item.get('expected_exit_codes',[0]*len(item['cases']))[case_index]
        ok=p.returncode==expected_exit and match and files_ok
        results.append({'exercise':item['id'],'input':inp,'expected':expected,'actual':actual,'passed':ok,'file_errors':file_errors})
        if file_errors:print('文件检查：',file_errors)
        print(item['id'],'PASS' if ok else 'FAIL',actual,flush=True)
if not results:raise SystemExit('没有匹配的原书题目，请检查 --chapter。')
report={'passed':sum(e['passed'] for e in results),'total':len(results),'results':results}
(ROOT/'guide'/('book-verification-'+args.chapter+'.json' if args.chapter else 'book-verification.json')).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
raise SystemExit(0 if all(e['passed'] for e in results) else 1)
