"""综合项目运行入口：保留命令行参数及所需的隔离运行库。"""
from pathlib import Path
import sys
from study import ROOT,build,call,linux_path,bash_command
def main():
    mode=sys.argv[1] if len(sys.argv)>1 else ''
    args=sys.argv[2:]
    if mode=='linux':
        source=ROOT/'linux/projects/score-report/reference.sh'
        return call(bash_command(source,*args)).returncode
    if mode in ('image','image-demo'):
        exe=build(ROOT/'opencv/projects/image-pipeline/main.cpp')
        if mode=='image-demo':
            from project_fixtures import prepare
            prepare()
            args=['--input',str(ROOT/'opencv/projects/image-pipeline/data/练习 图片.png'),'--output',str(ROOT/'opencv/projects/image-pipeline/output/demo-edges.png'),'--overwrite']
        return call([exe,*args]).returncode
    print('用法：run-project.py linux [Ubuntu格式CSV路径]，或image --input 图片 --output 结果.png，或image-demo')
    return 2
if __name__=='__main__':raise SystemExit(main())
