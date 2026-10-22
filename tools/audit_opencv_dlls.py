"""只读比较本地PE导入/导出表，定位OpenCV混合依赖。"""
from pathlib import Path
import struct,json
BIN=Path('D:/c++/MYSYS2/ucrt64/bin')
def inspect(path):
    data=path.read_bytes();pe=struct.unpack_from('<I',data,0x3c)[0];coff=pe+4
    nsec=struct.unpack_from('<H',data,coff+2)[0];optsz=struct.unpack_from('<H',data,coff+16)[0]
    opt=coff+20;is64=struct.unpack_from('<H',data,opt)[0]==0x20b;dd=opt+(112 if is64 else 96)
    sections=[]
    for i in range(nsec):
        offset=opt+optsz+40*i
        vs,va,rawsize,raw=struct.unpack_from('<IIII',data,offset+8)
        sections.append((va,max(vs,rawsize),raw))
    def offset(rva):
        for va,size,raw in sections:
            if va<=rva<va+size:return raw+rva-va
        return rva
    def string(rva):
        start=offset(rva);return data[start:data.index(0,start)].decode('ascii',errors='replace')
    exports=set();export_rva=struct.unpack_from('<I',data,dd)[0]
    if export_rva:
        e=offset(export_rva);count,names=struct.unpack_from('<I',data,e+24)[0],struct.unpack_from('<I',data,e+32)[0]
        for i in range(count):exports.add(string(struct.unpack_from('<I',data,offset(names)+4*i)[0]))
    imports={};import_rva=struct.unpack_from('<I',data,dd+8)[0]
    if import_rva:
        pos=offset(import_rva)
        while any(data[pos:pos+20]):
            original,_,_,name,first=struct.unpack_from('<IIIII',data,pos);dll=string(name);items=[]
            at=offset(original or first);width=8 if is64 else 4
            while True:
                thunk=struct.unpack_from('<Q' if is64 else '<I',data,at)[0]
                if not thunk:break
                if not thunk&(1<<(width*8-1)):items.append(string(thunk+2))
                at+=width
            imports[dll]=items;pos+=20
    return exports,imports
if __name__=='__main__':
    queue=['libopencv_video-413.dll','libopencv_objdetect-413.dll'];seen=set();cache={};problems=[]
    while queue:
        name=queue.pop()
        if name.lower() in seen:continue
        seen.add(name.lower());p=BIN/name
        if not p.exists():continue
        if name not in cache:cache[name]=inspect(p)
        for dll,symbols in cache[name][1].items():
            dep=BIN/dll
            if not dep.exists():continue
            if dll not in cache:cache[dll]=inspect(dep)
            missing=[s for s in symbols if s not in cache[dll][0]]
            if missing:problems.append({'module':name,'dependency':dll,'missing_count':len(missing),'examples':missing[:3]})
            queue.append(dll)
    print(json.dumps(problems,ensure_ascii=False,indent=2))
