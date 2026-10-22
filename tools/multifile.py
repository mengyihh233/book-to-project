"""仅为显式登记的多文件库练习选择实现文件，不通配收集main。"""

_EXERCISES = {
    'cpp/主教材/章节学习/第02章 函数与库/课后习题/第10题': 'combinatorics',
    'cpp/主教材/章节学习/第02章 函数与库/课后习题/第11题': 'calendar',
    'cpp/主教材/章节学习/第05章 集合类/课后习题/第05题': 'hist',
}


def _exercise(root, source):
    folder = source.parent.parent if source.parent.name == '我的作答' else source.parent
    try:
        relative = folder.relative_to(root).as_posix()
    except ValueError:
        return folder, None
    return folder, _EXERCISES.get(relative)


def student_entry(root, source):
    """把已登记的本人库实现/头文件反查到work入口；拒绝同题参考库。

    不根据文件名通配猜题，也不把任意同名文件视为个人作答。
    调用方仍负责检查真实文件、学习区边界及作答登记。
    """
    folder, name = _exercise(root, source)
    if not name:
        return source
    if source.name in (name + '.cpp', name + '.h'):
        if source.parent.name == '我的作答':
            return folder / 'work.cpp'
        raise ValueError('这是本题参考库。请打开“我的作答”下的库文件或work.cpp。')
    if source.name in ('reference.cpp', 'tests.cpp'):
        raise ValueError('这是参考实现或参考接口测试。请打开“我的作答”下的库文件或work.cpp。')
    return source


def companion_sources(root, source):
    if source.suffix != '.cpp':
        return []
    folder, name = _exercise(root, source)
    if not name:
        return []
    if source.name == name + '.cpp':
        raise ValueError('此文件是库实现，没有main；请选择reference.cpp、work.cpp或tests.cpp')
    if source.name not in ('reference.cpp', 'work.cpp', 'tests.cpp'):
        raise ValueError('该多文件练习请使用已登记的reference.cpp、work.cpp或tests.cpp入口')
    base = folder / '我的作答' if source.name == 'work.cpp' else folder
    return [base / (name + '.cpp')]
