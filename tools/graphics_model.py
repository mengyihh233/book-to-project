"""独立解析基本SVG图元，按几何模型检查内部填充；不执行SVG。"""
import xml.etree.ElementTree as ET
import math,re
def parse(text,width,height):
 if len(text)>200000 or '<!' in text:raise ValueError('SVG过大或含声明')
 root=ET.fromstring(text);ns='{http://www.w3.org/2000/svg}'
 if root.tag!=ns+'svg' or root.attrib!={'width':str(width),'height':str(height),'viewBox':f'0 0 {width} {height}'}:raise ValueError('SVG根尺寸/坐标错误')
 if root.text and root.text.strip():raise ValueError('SVG根有额外文本')
 shapes=[]
 for child in root:
  tag=child.tag.removeprefix(ns)
  fields={'x','y','width','height'} if tag=='rect' else {'cx','cy','rx','ry'} if tag=='ellipse' else set()
  if not fields or len(child) or set(child.attrib)-fields-{'fill','stroke','stroke-width'}:raise ValueError('只接受rect/ellipse及基本填充/描线')
  values={k:float(child.attrib[k]) for k in fields}
  if not all(math.isfinite(x) for x in values.values()):raise ValueError('非有限坐标')
  if any(values[k]<=0 for k in fields if k in ['width','height','rx','ry']):raise ValueError('宽高或半径必须为正')
  fill=child.attrib.get('fill','')
  if fill!='none' and not re.fullmatch('#[0-9a-fA-F]{6}',fill):raise ValueError('填充请用#RRGGBB或none')
  if 'stroke' in child.attrib and not re.fullmatch('#[0-9a-fA-F]{6}',child.attrib['stroke']):raise ValueError('描线颜色无效')
  if (child.text and child.text.strip()) or (child.tail and child.tail.strip()):raise ValueError('图元含多余文本')
  shapes.append((tag,values,fill.lower()))
 return shapes
def actual_color(shapes,x,y):
 color='#ffffff'
 for tag,v,fill in shapes:
  if fill=='none':continue
  inside=v['x']<=x<=v['x']+v['width'] and v['y']<=y<=v['y']+v['height'] if tag=='rect' else ((x-v['cx'])/v['rx'])**2+((y-v['cy'])/v['ry'])**2<=1
  if inside:color=fill
 return color
def expected_color(ex,w,h,x,y):
 if ex==16:
  colors=['#e53935','#fb8c00','#fdd835','#43a047','#1e88e5','#8e24aa','#87ceeb'];answer='#87ceeb'
  for b,c in enumerate(colors):
   if ((x/w-.5)/(.9-.035*b))**2+((y/h-1.35)/(1.2-.055*b))**2<=1:answer=c
  return answer
 if ex==17:
  size=.85*min(w,h);left=(w-size)/2;top=(h-size)/2
  u=(x-left)*8/size;v=(y-top)*8/size
  if not(0<=u<8 and 0<=v<8):return '#ffffff'
  col=int(u);row=int(v);dark=(col+row)%2==1
  if dark and (row<3 or row>=5) and (u-col-.5)**2+(v-row-.5)**2<=.36**2:return '#c0392b' if row<3 else '#30343b'
  return '#6d4c41' if dark else '#fff3e0'
 radius=.38*min(w,h);u=(x-w/2)/radius;v=(y-h/2)/radius
 if u*u+v*v>1:return '#ffffff'
 if u*u+(v+.5)**2<=.125**2:return '#000000'
 if u*u+(v-.5)**2<=.125**2:return '#ffffff'
 if u*u+(v+.5)**2<=.5**2:return '#ffffff'
 if u*u+(v-.5)**2<=.5**2:return '#000000'
 return '#ffffff' if u<=0 else '#000000'
def verify(text,ex,w,h):
 shapes=parse(text,w,h);count=0
 for row in range(53):
  for col in range(71):
   x=w*(col+.37)/71;y=h*(row+.29)/53
   expected=expected_color(ex,w,h,x,y);actual=actual_color(shapes,x,y)
   if expected!=actual:raise ValueError(f'题{ex} {w}x{h}: ({x:.2f},{y:.2f})期望{expected}，实际{actual}')
   count+=1
 return count
