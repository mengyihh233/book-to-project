"""检查当前题的个人作答；题目未配自动检查时明确说明，不伪报通过。"""
import argparse,json,subprocess,sys
from pathlib import Path
from multifile import student_entry
ROOT=Path(__file__).resolve().parents[1]
def plan(source):
    p=Path(source).resolve()
    if not p.is_relative_to(ROOT) or not p.is_file():raise ValueError('请选择本学习区内真实存在的个人作答文件。')
    if p.name.startswith(('reference','参考')) or '参考实现' in p.parts:raise ValueError('这是参考答案。请切换到自己的work.cpp或我的作答文件再检查。')
    rules=json.loads((ROOT/'tools/answer-cards.json').read_text(encoding='utf-8'))
    if p.name=='README.md':
        matches=[e for e in rules if (ROOT/e['guide']).resolve()==p]
        if len(matches)!=1:raise ValueError('这是章节或多题目录。请先打开具体题目的作答文件，再检查。')
        p=(ROOT/matches[0]['work']).resolve()
    p=student_entry(ROOT,p)
    item=next((e for e in rules if (ROOT/e['work']).resolve()==p),None)
    if not item:
        # 同一道题有两份作答：work.cpp（补写）与 from-scratch.cpp（从零写）。
        # 它们共用同一套登记样例，所以按“同目录”回退，不能要求各自登记一条规则。
        item=next((e for e in rules if (ROOT/e['work']).resolve().parent==p.parent),None)
    if not item:raise ValueError('这个文件还没有登记判分规则；编译成功不等于题目通过。请看本题README。')
    if item['check']=='book':
        args=['wsl-book-check.py','--work',str(p)] if sys.platform=='linux' else ['practice.py',str(p)]
    elif item['check']=='svg':args=['check-ch02-graphics.py','--file',str(p)]
    else:args=None
    return item,args

def emit_state(**info):
    print('##STATE## '+json.dumps(info,ensure_ascii=False),flush=True)

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('file');parser.add_argument('--只看规则',action='store_true',dest='explain');a=parser.parse_args()
    try:item,args=plan(a.file)
    except ValueError as e:
        print(e,file=sys.stderr)
        emit_state(state='unregistered' if '还没有登记判分规则' in str(e) else 'error')
        return 2
    print('题目：'+item['title'],flush=True);print('作答：'+item['work'],flush=True)
    if not args:
        print('本题没有独立自动判分。运行/编译只是观察结果，请按README的完成标准逐项自检。')
        print('仅展示检查规则，未执行评分，也没有记为完成。')
        emit_state(state='manual')
        return 0
    print('检查方式：'+('图形专项检查' if item['check']=='svg' else '固定输入输出样例检查')+'；不会自动记录个人学习完成。',flush=True)
    if a.explain:return 0
    result=subprocess.run([sys.executable,str(ROOT/'tools'/args[0]),*args[1:]],cwd=ROOT).returncode
    if result==3:print('本题尚未开始作答：没有执行样例比较，也没有记为完成。')
    elif result==4:print('本题编译失败：没有运行任何样例，不算通过也不算样例错误。')
    elif result==0:print('本题已通过登记检查；仍需复核未列出的边界。')
    else:print('本题检查未通过，请对照上方输入、期望和实际结果修改。')
    return result
if __name__=='__main__':raise SystemExit(main())
