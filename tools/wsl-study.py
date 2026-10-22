"""Ubuntu内的学习构建入口；不要用Windows Python运行。"""
import argparse,json,os,subprocess,sys,time
from multifile import companion_sources
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
CACHE=Path.home()/'.cache/book-learning'
def source(name):
 p=Path(name).resolve()
 if not p.is_relative_to(ROOT) or not p.is_file():raise ValueError('源码必须在学习区内')
 rel=p.relative_to(ROOT).as_posix()
 if not any(rel.startswith(x) for x in ('cpp/主教材/','cpp/语法小课/','opencv/','linux/','math/projects/')):raise ValueError('WSL入口当前支持C++主教材与语法小课、OpenCV、Linux和数学选做；其他环境请用对应Windows入口')
 return p
def build(p,active=False):
 if p.suffix not in ('.c','.cpp'):raise ValueError('请选择C/C++文件')
 out=CACHE/'active-program' if active else CACHE/'build'/p.relative_to(ROOT).with_suffix('.out')
 out.parent.mkdir(parents=True,exist_ok=True)
 cmd=['gcc' if p.suffix=='.c' else 'g++','-std=c11' if p.suffix=='.c' else '-std=c++17','-Wall','-Wextra','-Wpedantic','-g','-O0']
 libs=['-lm']
 if p.relative_to(ROOT).parts[0]=='opencv' or p.is_relative_to(ROOT/'math/projects/opencv'):cmd+=['-I/usr/include/opencv4'];libs+=['-lopencv_imgcodecs','-lopencv_imgproc','-lopencv_core']
 subprocess.run([*cmd,str(p),*[str(x) for x in companion_sources(ROOT,p)],'-o',str(out),*libs],check=True)
 return out
def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('mode',choices=['doctor','build','run','shell','lint','vision-demo']);parser.add_argument('file',nargs='?');parser.add_argument('--active',action='store_true');parser.add_argument('--input',type=Path);a=parser.parse_args()
 if sys.platform!='linux':raise ValueError('请在WSL Ubuntu中运行此入口')
 if a.mode=='doctor':
  subprocess.run(['bash',str(ROOT/'tools/doctor-linux.sh')],check=True);print('ROOT=',ROOT,'\nBUILD=',CACHE);return 0
 if a.mode=='vision-demo':
  exe=build(ROOT/'opencv/projects/parts-inspector/reference.cpp');sample=ROOT/'opencv/projects/parts-inspector/data/demo.png'
  if not sample.exists():raise ValueError('请先运行Windows机器视觉示例生成合成图')
  out=ROOT/'opencv/projects/parts-inspector/output'/f'wsl-{time.time_ns()}'
  request={'input':str(sample),'output':str(out),'threshold':100,'min_area':200,'max_area':100000,'invert':1}
  r=subprocess.run([str(exe)],input=json.dumps(request),text=True,check=True);print('结果目录：',out);return r.returncode
 if not a.file:raise ValueError('请指定当前源码文件')
 p=source(a.file)
 if a.mode in ('shell','lint'):
  if p.suffix!='.sh' or not p.is_relative_to(ROOT/'linux'):raise ValueError('请选择Linux主线的.sh文件')
  if a.mode=='lint':return subprocess.run(['shellcheck',str(p)]).returncode
  if b'\r\n' in p.read_bytes():raise ValueError('此脚本使用CRLF换行，请在VS Code右下角切换LF并保存后运行；未自动改写你的作答')
  sandbox=CACHE/'sandbox'/p.parent.relative_to(ROOT);sandbox.mkdir(parents=True,exist_ok=True)
  return subprocess.run(['bash',str(p)],cwd=sandbox,env={**os.environ,'DATA':str(ROOT/'linux/data')}).returncode
 exe=build(p,a.active)
 if a.mode=='build':print(exe);return 0
 if a.input:
  with a.input.open('rb') as f:return subprocess.run([str(exe)],stdin=f,cwd=p.parent).returncode
 return subprocess.run([str(exe)],cwd=p.parent).returncode
if __name__=='__main__':
 try:raise SystemExit(main())
 except (ValueError,OSError,subprocess.CalledProcessError) as e:print('学习任务失败：',e,file=sys.stderr);raise SystemExit(2)
