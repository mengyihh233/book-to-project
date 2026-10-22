"""Stream local PDFs with one byte range; never read an entire textbook into RAM."""
import re
def serve_pdf(handler,path,head=False):
 stat=path.stat();size=stat.st_size;etag=f'"{stat.st_mtime_ns:x}-{size:x}"';modified=handler.date_time_string(stat.st_mtime)
 value=handler.headers.get('Range');condition=handler.headers.get('If-Range')
 if condition and condition not in (etag,modified):value=None
 start,end=0,size-1
 if value:
  match=re.fullmatch(r'bytes=(\d*)-(\d*)',value)
  try:
   if not match or not any(match.groups()):raise ValueError('range format')
   first,last=match.groups()
   if first:start=int(first);end=min(int(last),size-1) if last else size-1
   else:
    length=int(last)
    if length<=0:raise ValueError('empty suffix')
    start=max(0,size-length);end=size-1
   if start>=size or start>end:raise ValueError('range beyond file')
  except ValueError:
   handler.send_response(416);handler.send_header('Content-Range',f'bytes */{size}');handler.send_header('Content-Length','0');handler.send_header('Accept-Ranges','bytes');handler.end_headers();return
 length=max(0,end-start+1)
 handler.send_response(206 if value else 200);handler.send_header('Content-Type','application/pdf');handler.send_header('Accept-Ranges','bytes');handler.send_header('Content-Length',str(length));handler.send_header('ETag',etag);handler.send_header('Last-Modified',modified)
 if value:handler.send_header('Content-Range',f'bytes {start}-{end}/{size}')
 handler.end_headers()
 if head:return
 try:
  with path.open('rb') as stream:
   stream.seek(start)
   while length:
    chunk=stream.read(min(65536,length))
    if not chunk:break
    handler.wfile.write(chunk);length-=len(chunk)
 except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):pass
