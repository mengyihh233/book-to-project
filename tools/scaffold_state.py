"""判断引导框架的补全区是否仍为空模板。

只读源码文本，不编译、不判分、不改文件。
目的：把“还没开始写”与“写了但样例没过”分开，避免空模板因为占位 throw
恰好返回了某个样例期望的退出码而被误报为通过。
"""
import re
from multifile import companion_sources

# /* BEGIN 1：标题 */ ... /* END 1 */
_REGION = re.compile(r'/\*\s*BEGIN\s+(\d+)([^*]*?)\*/(.*?)/\*\s*END\s+\1\s*\*/', re.S)
_BLOCK_COMMENT = re.compile(r'/\*.*?\*/', re.S)
_LINE_COMMENT = re.compile(r'//[^\n]*')
PLACEHOLDER = '补全区尚未完成'
# 两道早期多文件题的给定库实现。只认这些完整占位throw，不把普通TODO注释
# 或已经写出的函数当空题；也兼容后来加在这些函数外面的BEGIN/END标记。
_LIBRARY_STUB = re.compile(
    r'throw\s+std::logic_error\s*\(\s*"TODO '
    r'(permutations|combinations|isLeapYear|daysInMonth|monthToString)"\s*\)\s*;'
)
_GUIDED_STUB = re.compile(
    r'throw\s+std::logic_error\s*\(\s*"补全区尚未完成'
    r'(?:[：:]\s*[A-Za-z_][A-Za-z_0-9]*)?"\s*\)\s*;'
)


def _code_only(code):
    """去掉注释与全部空白，只留真正会被编译的字符。"""
    code = _BLOCK_COMMENT.sub(' ', code)
    code = _LINE_COMMENT.sub(' ', code)
    return re.sub(r'\s+', '', code)


def unfinished_regions(text):
    """返回仍未填写的补全区 [(编号, 标题), ...]。

    没有 BEGIN/END 标记的文件返回空列表，调用方应保持原有行为。
    """
    found = []
    for match in _REGION.finditer(text or ''):
        body = _code_only(match.group(3))
        bare = _BLOCK_COMMENT.sub(' ', _LINE_COMMENT.sub(' ', match.group(3))).strip()
        if not body or _GUIDED_STUB.fullmatch(bare) or _LIBRARY_STUB.fullmatch(bare):
            found.append((int(match.group(1)), match.group(2).strip(' \t:：')))
    return found


def describe(regions):
    """把未填写的补全区拼成学生看得懂的一句话。"""
    return '、'.join(
        'BEGIN %d%s' % (number, '（%s）' % title if title else '')
        for number, title in regions
    )


# 早期模板里 main 只打印这句话就 return 2；学生不会自己写这句。
_STUB_MARK = 'TODO: implement exercise'


def template_reason(text):
    """判断作答是否还没开始。

    返回一句可以直接展示的中文说明；已经有真实实现时返回 None。
    """
    regions = unfinished_regions(text)
    if regions:
        return '补全区还是空模板（%s），里面只有引导注释或占位代码' % describe(regions)
    if _STUB_MARK in (text or ''):
        return '作答文件还是空模板：只有 TODO 提示，没有自己的实现'
    code = _BLOCK_COMMENT.sub(' ', _LINE_COMMENT.sub(' ', text or ''))
    stubs = list(dict.fromkeys(_LIBRARY_STUB.findall(code)))
    if stubs:
        return '库函数仍是给定的 TODO 占位（%s），请实现这些函数' % '、'.join(stubs)
    return None


def source_template_reason(root, source):
    """检查与真实构建一致的入口和伴随源码，绝不顺便读取参考实现。"""
    for path in [source, *companion_sources(root, source)]:
        # 缺文件交给后续真实编译诊断，不能把它报告成尚未开始。
        if not path.is_file():
            continue
        reason = template_reason(path.read_text(encoding='utf-8', errors='replace'))
        if reason:
            return path.relative_to(root).as_posix() + '：' + reason
    return None
