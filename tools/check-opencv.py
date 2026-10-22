from study import ROOT,build,call
import json,time
exercises=[e for e in json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8')) if e['id'].startswith('opencv-')]
rows=[]
for e in exercises:
    start=time.time()
    try:
        exe=build(ROOT/e['source'])
        result=call([exe],capture_output=True,text=True,encoding='utf-8',timeout=30,cwd=ROOT)
        ok=result.returncode==0;output=result.stdout+result.stderr;exit_code=result.returncode
    except Exception as err:ok=False;output=str(err);exit_code=None
    rows.append({'id':e['id'],'passed':ok,'exit_code':exit_code,'seconds':round(time.time()-start,2),'output':output})
    print(e['id'],'通过' if ok else '失败',flush=True)
report={'checked_at':time.strftime('%Y-%m-%d %H:%M:%S'),'passed':sum(r['passed'] for r in rows),'total':len(rows),'library':'4.13.0','results':rows}
(ROOT/'guide/OpenCV验证记录.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
raise SystemExit(0 if all(r['passed'] for r in rows) else 1)
