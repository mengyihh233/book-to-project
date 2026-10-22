"""Read-only consistency audit for the existing parts-inspector JSON reports."""
import argparse,csv,io,json,math,sys
from pathlib import Path

def integer(value,name,minimum=0):
    if type(value) is not int or value<minimum:raise ValueError(name+' must be an integer >= '+str(minimum))
    return value

def number(value,name):
    if type(value) not in (int,float):raise ValueError(name+' must be numeric')
    try:value=float(value)
    except OverflowError:raise ValueError(name+' is too large') from None
    if not math.isfinite(value):raise ValueError(name+' must be finite')
    return value

def no_duplicates(pairs):
    result={}
    for key,value in pairs:
        if key in result:raise ValueError('duplicate JSON key: '+key)
        result[key]=value
    return result

def audit(path):
    path=Path(path)
    if path.is_symlink() or not path.is_file():raise ValueError('regular report file required')
    if path.stat().st_size>8*1024*1024:raise ValueError('report exceeds 8 MiB teaching limit')
    data=json.loads(path.read_text(encoding='utf-8-sig'),object_pairs_hook=no_duplicates,parse_constant=lambda x:(_ for _ in ()).throw(ValueError('non-JSON numeric constant: '+x)))
    if not isinstance(data,dict):raise ValueError('report object required')
    width=integer(data.get('width'),'width',1);height=integer(data.get('height'),'height',1);count=integer(data.get('count'),'count')
    objects=data.get('objects')
    if not isinstance(objects,list) or len(objects)!=count:raise ValueError('count differs from objects length')
    areas=[];ids=set()
    for obj in objects:
        if not isinstance(obj,dict):raise ValueError('object entry must be an object')
        ident=integer(obj.get('id'),'id',1)
        if ident in ids:raise ValueError('duplicate object id')
        ids.add(ident)
        x=integer(obj.get('x'),'x');y=integer(obj.get('y'),'y');w=integer(obj.get('width'),'box width',1);h=integer(obj.get('height'),'box height',1)
        if x+w>width or y+h>height:raise ValueError('bounding box outside image')
        area=number(obj.get('area'),'area');cx=number(obj.get('cx'),'cx');cy=number(obj.get('cy'),'cy')
        if not 0<area<=w*h:raise ValueError('invalid contour area')
        if not (x<=cx<x+w and y<=cy<y+h):raise ValueError('centroid outside box')
        areas.append(area)
    total=math.fsum(areas)
    if not math.isfinite(total):raise ValueError('total area overflow')
    return [str(path),count,format(total,'.12g'),format(total/count if count else 0,'.12g')]

def main(argv=None):
    if hasattr(sys.stdout,'reconfigure'):sys.stdout.reconfigure(encoding='utf-8')
    if hasattr(sys.stderr,'reconfigure'):sys.stderr.reconfigure(encoding='utf-8')
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('reports',nargs='+',type=Path);args=parser.parse_args(argv)
    try:
        if len(args.reports)>1000:raise ValueError('at most 1000 reports per invocation')
        resolved=[p.resolve() for p in args.reports]
        if len(set(resolved))!=len(resolved):raise ValueError('duplicate input report')
        rows=[audit(p) for p in args.reports]
    except (ValueError,OSError,UnicodeError,OverflowError) as e:
        print('report audit failed: '+str(e),file=sys.stderr);return 2
    output=io.StringIO(newline='');writer=csv.writer(output,lineterminator='\n');writer.writerow(['file','count','total_contour_area_px2','mean_contour_area_px2']);writer.writerows(rows)
    sys.stdout.write(output.getvalue());return 0

if __name__=='__main__':raise SystemExit(main())
