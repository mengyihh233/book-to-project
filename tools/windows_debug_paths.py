"""ASCII debugger paths for MinGW/GDB; junctions point to the real source folders."""
from pathlib import Path
import hashlib, os, re, subprocess

def alias_for(root, directory):
    key=hashlib.sha256(directory.relative_to(root).as_posix().encode('utf-8')).hexdigest()[:20]
    return root/'build/debug-sources'/key

def prefix_options(root, sources):
    if os.name!='nt':return []
    root=root.resolve();pending=list(sources);seen=set();directories=set()
    while pending:
        source=Path(pending.pop()).resolve()
        if source in seen or not source.is_file() or not source.is_relative_to(root):continue
        seen.add(source);directories.add(source.parent)
        for include in re.findall(r'^\s*#\s*include\s*"([^"\n]+)"',source.read_text(encoding='utf-8-sig'),re.M):
            pending.append(source.parent/include)
    options=[]
    for directory in sorted(directories):
        if directory.as_posix().isascii():continue
        alias=alias_for(root,directory)
        alias.parent.mkdir(parents=True,exist_ok=True)
        if alias.exists():
            if alias.resolve()!=directory:raise ValueError('Debugger source alias points to an unexpected folder')
        else:
            literal=lambda p:"'"+str(p).replace("'","''")+"'"
            command='$null=New-Item -ItemType Junction -Path '+literal(alias)+' -Target '+literal(directory)
            subprocess.run(['powershell.exe','-NoLogo','-NoProfile','-NonInteractive','-Command',command],check=True,capture_output=True)
        # GCC accepts source filenames with either Windows or POSIX separators.
        options.extend([f'-fdebug-prefix-map={directory}={alias}',f'-fdebug-prefix-map={directory.as_posix()}={alias.as_posix()}'])
    return options
