"""固定合成图的视觉失败场景实验；只运行现有参考，不写个人作答或进度。"""
import argparse, hashlib, json, time
from pathlib import Path
from PIL import Image, ImageDraw
from study import ROOT, build, call

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run',action='store_true',help='生成一轮新实验并运行现有检测参考')
    parser.add_argument('--output',type=Path,help='可选：项目output下尚不存在的目录')
    args=parser.parse_args()
    if not args.run:
        parser.print_help();return 0
    parent=(ROOT/'opencv/projects/parts-inspector/output').resolve()
    out=(args.output or parent/f'failure-lab-{time.time_ns()}').resolve()
    if not out.is_relative_to(parent) or out==parent:parser.error('输出必须位于零件项目output内的新子目录')
    if out.exists():parser.error('目录已存在，换一个新目录；本工具不覆盖或删除')
    exe=build(ROOT/'opencv/projects/parts-inspector/reference.cpp')
    parent.mkdir(parents=True,exist_ok=True);out.mkdir()
    def scene(background=230):
        image=Image.new('RGB',(240,160),(background,)*3);draw=ImageDraw.Draw(image)
        draw.rectangle((30,40,79,89),fill=(30,)*3)
        draw.rectangle((130,40,179,89),fill=(30,)*3)
        return image
    normal=scene();connected=normal.copy();ImageDraw.Draw(connected).rectangle((80,60,129,69),fill=(30,)*3)
    hole=Image.new('RGB',(240,160),(230,)*3);draw=ImageDraw.Draw(hole);draw.rectangle((30,40,79,89),fill=(30,)*3);draw.rectangle((45,55,64,74),fill=(230,)*3)
    small=normal.resize((120,80),Image.Resampling.NEAREST)
    cases=[
      ('baseline','分离、光照正常',normal,100,200,2,2),
      ('dark-background','整体偏暗，固定阈值失效',scene(80),100,200,2,1),
      ('wrong-threshold','阈值低于物体灰度',normal,20,200,2,0),
      ('touching','两件之间加连接桥',connected,100,200,2,1),
      ('hole','一件带孔零件',hole,100,200,1,1),
      ('scaled-old-area','尺寸减半但面积阈值未调',small,100,1000,2,0),
      ('scaled-new-area','尺寸减半、面积阈值除以4',small,100,250,2,2),
      ('blank','空白背景，没有放入零件',Image.new('RGB',(240,160),(230,)*3),100,200,0,0),
    ]
    results=[]
    for ident,title,image,threshold,min_area,truth,expected in cases:
        source=out/(ident+'.png');image.save(source);before=hashlib.sha256(source.read_bytes()).hexdigest()
        target=out/(ident+'-result');request=dict(input=source.as_posix(),output=target.as_posix(),threshold=threshold,min_area=min_area,max_area=100000,invert=1)
        process=call([exe],input=json.dumps(request,ensure_ascii=False),text=True,capture_output=True,timeout=20)
        if process.returncode:raise RuntimeError(f'{ident}: '+process.stderr)
        report=json.loads((target/'report.json').read_text(encoding='utf-8'))
        count=report['count'];assert count==len(report['objects'])==expected,(ident,count,expected)
        assert before==hashlib.sha256(source.read_bytes()).hexdigest(),'源图被修改'
        with Image.open(target/'mask.png') as mask:foreground=mask.convert('L').histogram()[255]
        area=sum(o['area'] for o in report['objects'])
        result=dict(id=ident,title=title,truth_count=truth,expected_observed_count=expected,observed_count=count,agrees_with_truth=count==truth,threshold=threshold,min_area=min_area,foreground_pixels=foreground,total_external_contour_area=area,input=source.relative_to(ROOT).as_posix(),report=(target/'report.json').relative_to(ROOT).as_posix())
        results.append(result);print(f'{ident}: truth={truth}, observed={count}, expected={expected}')
    hole_result=next(r for r in results if r['id']=='hole');assert hole_result['foreground_pixels']==2100 and hole_result['total_external_contour_area']==2401
    reports=[ROOT/r['report'] for r in results]
    metrics=call([__import__('sys').executable,ROOT/'linux/projects/dataset-audit/report-metrics.py',*reports],capture_output=True,text=True,timeout=15)
    assert metrics.returncode==0,metrics.stderr
    (out/'report-metrics.csv').write_text(metrics.stdout,encoding='utf-8-sig')
    summary=dict(kind='自编固定输入教学实验，非通用准确率评测',cases=results,all_expected_observations_verified=True,known_wrong_counts=sum(not r['agrees_with_truth'] for r in results),note='失败案例得到预期错误结果，表示边界演示复现成功，不表示检测器正确；报告通过内部一致性核对也不证明与图像真值一致。')
    (out/'实验结果.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    # 仅发布本工具生成的合成场景，网页只展示结果，不执行C++。
    (ROOT/'workbench/vision-lab.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print('实验目录：',out);return 0

if __name__=='__main__':raise SystemExit(main())
