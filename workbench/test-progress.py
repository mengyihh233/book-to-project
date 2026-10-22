"""隔离临时学习目录测试，绝不写真实学习记录。"""
import csv,json,tempfile,threading,urllib.request,urllib.error
from pathlib import Path
import server
real_root=server.ROOT
with tempfile.TemporaryDirectory(dir=real_root/'build') as tmp:
 server.ROOT=Path(tmp);(server.ROOT/'guide').mkdir()
 dest=server.ROOT/'guide/学习进度.csv'
 fields=['题号','任务类型','状态','开始日期','完成日期','复盘']
 with dest.open('w',encoding='utf-8-sig',newline='') as f:
  w=csv.DictWriter(f,fieldnames=fields);w.writeheader();w.writerow(dict(zip(fields,['TEST-01','配套练习','未开始','','','保留内容'])))
 http=server.ThreadingHTTPServer(('127.0.0.1',0),server.Handler);threading.Thread(target=http.serve_forever,daemon=True).start()
 url=f'http://127.0.0.1:{http.server_port}/api/progress'
 def post(body,origin=None):
  req=urllib.request.Request(url,json.dumps(body).encode(),{'Content-Type':'application/json',**({'Origin':origin} if origin else {})})
  try:
   with urllib.request.urlopen(req) as r:return r.status
  except urllib.error.HTTPError as e:return e.code
 assert post({'id':'TEST-01','status':'学习中','note':'中文复盘'})==200
 assert server.progress()[0]['复盘']=='中文复盘'
 assert post({'id':'TEST-01','status':'已完成'})==200
 assert server.progress()[0]['完成日期']
 before=dest.read_bytes()
 assert post({'id':'不存在','status':'已完成'})==400
 assert post({'id':'TEST-01','status':'错误状态'})==400
 assert post({'id':'TEST-01','status':'已完成'},'https://example.org')==400
 assert dest.read_bytes()==before
 http.shutdown();server.ROOT=real_root
print('PASS: 保存、日期、中文、未知题号、非法状态、跨站请求；真实进度未修改。')
