"""按题目约定比较输出；数值字段容差仅由显式元数据启用。"""
import math
def matches(actual,expected,item=None):
    item=item or {}
    if actual==expected:return True
    if item.get('exact_output'):return False
    rel=item.get('rel_tol',1e-10);absolute=item.get('abs_tol',1e-9)
    def number(a,b):
        try:
            x,y=float(a),float(b)
            return math.isfinite(x) and math.isfinite(y) and math.isclose(x,y,rel_tol=rel,abs_tol=absolute)
        except ValueError:return False
    if item.get('numeric_tokens'):
        a,b=actual.split(),expected.split()
        return len(a)==len(b) and bool(a) and all(number(x,y) for x,y in zip(a,b))
    return number(actual,expected)
