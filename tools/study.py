"""Build/run one learning file, or verify all supplied reference solutions."""
from pathlib import Path
import subprocess, sys, os, json, hashlib, time, shutil
from multifile import companion_sources
from windows_debug_paths import prefix_options

ROOT = Path(__file__).resolve().parent.parent

def _compiler_dir():
    """编译器目录：环境变量 > MSYS2 常见位置 > PATH 里的 g++。"""
    custom = os.environ.get('BOOK_STUDY_BIN')
    if custom:
        return Path(custom)
    default = Path('D:/c++/MYSYS2/ucrt64/bin')
    if default.is_dir():
        return default
    found = shutil.which('g++') or shutil.which('clang++')
    return Path(found).resolve().parent if found else default

BIN = _compiler_dir()
ENV = dict(os.environ, PATH=str(ROOT/'vendor/fltk/ucrt64/bin')+os.pathsep+str(BIN)+os.pathsep+os.environ.get('PATH',''), PYTHONIOENCODING='utf-8')

def call(args, **kw):
    if kw.get('text') and 'encoding' not in kw:
        kw['encoding']='utf-8'
        kw.setdefault('errors','replace')
    environment=dict(ENV)
    executable=str(args[0]).replace('\\','/').lower()
    if executable.startswith(((ROOT.as_posix()+'/build/opencv/').lower(),(ROOT.as_posix()+'/build/math/projects/opencv/').lower())):
        environment['PATH']=str(ROOT/'vendor/opencv-deps/ucrt64/bin')+os.pathsep+environment['PATH']
    environment.update(kw.pop('env',{}))
    return subprocess.run([str(a) for a in args], env=environment, **kw)

def valid_source(name, suffix):
    p=Path(name).resolve()
    suffixes=(suffix,) if isinstance(suffix,str) else suffix
    if ROOT not in p.parents or p.suffix not in suffixes or not p.is_file():
        raise ValueError(f'Choose a {suffix} file inside {ROOT}')
    return p

def build(name,active=False):
    p=valid_source(name,('.cpp','.c'))
    out=ROOT/'build/active-program.exe' if active else ROOT/'build'/p.relative_to(ROOT).with_suffix('.exe')
    # MinGW's Windows linker may decode non-ASCII output paths with the ANSI
    # code page. Keep learning source folders Chinese and generated binaries in
    # a stable ASCII cache; the active F5 executable already has an ASCII path.
    if not active and not out.as_posix().isascii():
        key=hashlib.sha256(p.relative_to(ROOT).as_posix().encode('utf-8')).hexdigest()[:20]
        out=ROOT/'build/cpp-cache'/key/(p.stem+'.exe')
    out.parent.mkdir(parents=True,exist_ok=True)
    compiler=BIN/('gcc.exe' if p.suffix=='.c' else 'g++.exe')
    standard='-std=c11' if p.suffix=='.c' else '-std=c++17'
    options=['-I',ROOT/'vendor/ppp2'] if p.suffix=='.cpp' else []
    links=['-lm']
    if 'opencv' in p.relative_to(ROOT).parts:
        options+=['-I',BIN.parent/'include/opencv4','-L',BIN.parent/'lib','-finput-charset=UTF-8','-fexec-charset=UTF-8']
        links+=['-lopencv_ml','-lopencv_objdetect','-lopencv_video','-lopencv_calib3d','-lopencv_features2d','-lopencv_flann','-lopencv_videoio','-lopencv_highgui','-lopencv_imgcodecs','-lopencv_imgproc','-lopencv_core']
        if 'image-pipeline' in p.relative_to(ROOT).parts:links+=['-lshell32']
    if 'opengl' in p.relative_to(ROOT).parts:
        links+=['-lglfw3','-lglew32','-lopengl32','-lgdi32']
    if '图形界面练习' in p.relative_to(ROOT).parts:
        options+=['-I',ROOT/'vendor/fltk/ucrt64/include','-L',ROOT/'vendor/fltk/ucrt64/lib']
        links+=['-lfltk']
    extra=companion_sources(ROOT,p)
    if p.suffix=='.cpp' and any(h in p.read_text(encoding='utf-8') for h in ('"Simple_window.h"','"Graph.h"','"GUI.h"')):
        adapted=ROOT/'vendor/ppp2-adapted'
        options=['-I',adapted,'-include',adapted/'std_lib_facilities.h',*options]
        if '图形界面练习' not in p.relative_to(ROOT).parts:
            options+=['-I',ROOT/'vendor/fltk/ucrt64/include','-L',ROOT/'vendor/fltk/ucrt64/lib']
        extra=[adapted/(n+'.cpp') for n in ('Graph','GUI','Window')]
        links=['-lfltk_images','-lfltk',*links]
    debug_options=prefix_options(ROOT,[p,*extra])
    call([compiler,standard,'-Wall','-Wextra','-Wpedantic','-g','-O0',*debug_options,*options,p,*extra,'-o',out,*links],check=True)
    return out

def linux_path(p):
    p=Path(p).resolve()
    return '/mnt/'+p.drive[0].lower()+p.as_posix()[2:]

GIT_BASH=Path('D:/Git/bin/bash.exe')

def wsl_distribution():
    settings=ROOT/'tools/runtime-settings.json'
    pref=json.loads(settings.read_text(encoding='utf-8-sig')) if settings.exists() else {}
    name=pref.get('distribution','Ubuntu-22.04')
    if not isinstance(name,str) or not name.strip():raise ValueError('WSL distribution 设置不能为空')
    return name.strip()
def use_git_bash():
    pref=json.loads((ROOT/'tools/runtime-settings.json').read_text(encoding='utf-8')) if (ROOT/'tools/runtime-settings.json').exists() else {}
    return os.environ.get('BOOK_STUDY_SHELL',pref.get('shell_backend','git'))=='git' and GIT_BASH.exists()
def bash_path(p):
    p=Path(p).resolve()
    return '/'+p.drive[0].lower()+p.as_posix()[2:]

def bash_command(script,*args):
    if use_git_bash():
        converted=[bash_path(x) if isinstance(x,Path) else ('/'+x[5:] if isinstance(x,str) and x.startswith('/mnt/') else x) for x in args]
        return [GIT_BASH,bash_path(script),*converted]
    return ['wsl.exe','-d',wsl_distribution(),'--','bash',linux_path(script),*[linux_path(x) if isinstance(x,Path) else x for x in args]]

def shell(name,lint=False,capture=False):
    p=valid_source(name,'.sh')
    relative=p.relative_to(ROOT/'linux')
    if relative.parts[0] not in ('chapters','projects'):raise ValueError('请选择Linux章节或项目内的脚本')
    sandbox=ROOT/'linux'/'sandbox'/relative.parent
    # chNN paths include their chapter folder; distinct folders for book exercises.
    sandbox.mkdir(parents=True,exist_ok=True)
    if lint:
        if use_git_bash():
            print('使用 bash -n 语法检查；不等同于 ShellCheck 静态分析。',flush=True)
            return call([GIT_BASH,'-n',bash_path(p)],capture_output=capture,text=True,timeout=30)
        return call(['wsl.exe','-d',wsl_distribution(),'--','shellcheck',linux_path(p)],capture_output=capture,text=True)
    if use_git_bash():
        return call(bash_command(p),capture_output=capture,text=True,timeout=30,cwd=sandbox,env={'DATA':bash_path(ROOT/'linux/data')})
    return call(['wsl.exe','-d',wsl_distribution(),'--','env','DATA=仓库根目录/linux/data','bash','仓库根目录/tools/run-shell.sh',linux_path(sandbox),linux_path(p)],capture_output=capture,text=True,timeout=30)

def doctor():
    checks={}
    shell_check=('Git Bash（基础Shell练习，非完整Linux）',[GIT_BASH,'--version']) if use_git_bash() else ('Ubuntu tools',['wsl.exe','-d',wsl_distribution(),'--','bash','仓库根目录/tools/doctor-linux.sh'])
    for label,args in [('Windows G++',[BIN/'g++.exe','--version']),('Windows GDB',[BIN/'gdb.exe','--version']),shell_check]:
        r=call(args,capture_output=True,text=True,timeout=40)
        print(label+': '+('OK' if r.returncode==0 else 'MISSING'))
        print((r.stdout+r.stderr)[:1700])
        checks[label]=r.returncode==0
    return checks

def verify():
    manifest=json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8'))
    rows=[]
    for e in manifest:
        p=ROOT/e['source'];start=time.time()
        try:
            if p.suffix in ('.cpp','.c'):
                out=build(p)
                r=call([out],capture_output=True,text=True,timeout=15,cwd=ROOT)
            else:
                r=shell(p,capture=True)
            ok=r.returncode==0
            note=(r.stdout+r.stderr)[-2500:]
        except Exception as ex:
            ok=False;note=str(ex)
        rows.append({'id':e['id'],'passed':ok,'seconds':round(time.time()-start,2),'output':note})
        print(e['id'], 'PASS' if ok else 'FAIL',flush=True)
    result={'checked_at':time.strftime('%Y-%m-%d %H:%M:%S'),'results':rows,'passed':sum(r['passed'] for r in rows),'total':len(rows)}
    (ROOT/'guide/verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    print(f"{result['passed']}/{result['total']} reference programs passed")
    return all(x['passed'] for x in rows)

if __name__=='__main__':
    try:
        mode=sys.argv[1] if len(sys.argv)>1 else 'doctor'
        if mode in ('run','build'):
            p=valid_source(sys.argv[2],('.cpp','.c'))
            if mode=='build' and sys.argv[3:] not in ([],['--active']):raise ValueError('build 仅支持可选 --active')
            out=build(p,active=mode=='build' and sys.argv[3:]==['--active'])
            if mode=='run':
                if len(sys.argv)>3:
                    if len(sys.argv)!=5 or sys.argv[3]!='--input':raise ValueError('文件输入用法：run 源码 --input 输入文件')
                    input_path=Path(sys.argv[4]).resolve()
                    if ROOT not in input_path.parents or not input_path.is_file():raise ValueError('输入文件必须在学习区内')
                    with input_path.open('rb') as stream:sys.exit(call([out],cwd=p.parent,stdin=stream,timeout=30).returncode)
                sys.exit(call([out],cwd=p.parent).returncode)
        elif mode in ('shell','lint'):sys.exit(shell(sys.argv[2],lint=mode=='lint').returncode)
        elif mode=='verify':sys.exit(0 if verify() else 1)
        elif mode=='doctor':sys.exit(0 if all(doctor().values()) else 1)
        else:raise ValueError('Use doctor, run, build, shell, lint, or verify')
    except (ValueError,subprocess.CalledProcessError,subprocess.TimeoutExpired) as e:
        print(e,file=sys.stderr);sys.exit(1)
