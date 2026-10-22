"""用已登记的原书验收样例检查当前作答，不修改学习进度。"""
from pathlib import Path
import sys,json,math
from study import ROOT,build,call,valid_source
from answer_compare import matches
from file_cases import case_directory,verify_case_files
from scaffold_state import source_template_reason

# 给网页用的机器可读状态：不看中文措辞，也不受编码影响。
def emit_state(**info):
    print('##STATE## '+json.dumps(info,ensure_ascii=False))

def main():
    source=valid_source(sys.argv[1],('.cpp','.c'))
    reason=source_template_reason(ROOT,source)
    if reason:
        print('本题尚未开始作答：'+reason+'。')
        print('这不是编译失败，也不是样例未通过。按题目要求写出自己的实现后，再运行“本题：检查作答”。')
        emit_state(state='unfinished')
        return 3
    tests=json.loads((ROOT/'tools/book-tests.json').read_text(encoding='utf-8'))
    item=next((e for e in tests if (ROOT/e['source']).parent.resolve()==source.parent),None)
    if item is None:
        print('当前文件没有登记原书输入输出样例。请按本章README添加测试；此工具目前支持book-exercises中的已覆盖题目。')
        emit_state(state='unregistered')
        return 2
    try:
        exe=build(source)
    except Exception:
        print('编译失败：没有生成可执行程序，因此一组样例都没有运行。')
        print('请按上方编译器给出的行号和原因修改，再重新检查。')
        emit_state(state='compile-error')
        return 4
    passed=0
    for i,(inp,expected) in enumerate(item['cases']):
        try:
            with case_directory(item,source.parent) as folder:
                r=call([exe],input=inp,capture_output=True,text=True,timeout=10,cwd=folder)
                files_ok,file_errors=verify_case_files(item,i,folder)
            actual=r.stdout if item.get('preserve_all_output') else (r.stdout.removesuffix('\n') if item.get('preserve_output') else r.stdout.strip())
            if item.get('last_line'):actual=actual.splitlines()[-1] if actual else ''
            expected_exit=item.get('expected_exit_codes',[0]*len(item['cases']))[i]
            ok=r.returncode==expected_exit and matches(actual,expected,item) and files_ok
            if file_errors:print('文件检查：',file_errors)
            print(f'样例{i+1}：'+('通过' if ok else '未通过'))
            if not ok:print(f'输入：{inp!r}\n期望：{expected!r}，退出码{expected_exit}\n实际：{actual!r}，退出码{r.returncode}')
            passed+=ok
        except Exception as e:print(f'样例{i+1}：执行失败，{e}')
    print(f'通过 {passed}/{len(item["cases"])}。这只是固定样例结果，仍需自己补充边界情况。')
    emit_state(state='passed' if passed==len(item['cases']) else 'failed', passed=passed, total=len(item['cases']))
    return 0 if passed==len(item['cases']) else 1
if __name__=='__main__':raise SystemExit(main())
