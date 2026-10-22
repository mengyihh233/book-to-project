"""原书文件题的隔离夹具；退出上下文后自动清理，不访问个人作答目录。"""
from pathlib import Path, PurePosixPath
from tempfile import TemporaryDirectory
from contextlib import contextmanager
@contextmanager
def case_directory(item, fallback=None):
    if 'fixtures' not in item:
        yield fallback
        return
    with TemporaryDirectory(prefix='book-ch04-') as folder:
        root=Path(folder)
        for name, text in item['fixtures'].items():
            rel=PurePosixPath(name)
            if rel.is_absolute() or '..' in rel.parts or ':' in name or '\\' in name:
                raise ValueError('unsafe fixture path')
            dest=root.joinpath(*rel.parts)
            dest.parent.mkdir(parents=True,exist_ok=True)
            dest.write_bytes(text.encode('utf-8'))
        yield root

def verify_case_files(item,index,folder):
    """在临时目录销毁前检查生成文件和输入完整性，按UTF-8字节精确比较。"""
    checks=item.get('file_expectations',[])
    if not checks and not item.get('check_fixture_integrity'):return True,[]
    if folder is None:raise ValueError('file checks require a fixture directory')
    root=Path(folder).resolve();errors=[]
    wanted=dict(item.get('fixtures',{})) if item.get('check_fixture_integrity') else {}
    wanted.update(checks[index] if checks else {})
    for name,text in wanted.items():
        rel=PurePosixPath(name)
        if rel.is_absolute() or '..' in rel.parts or ':' in name or '\\' in name:
            raise ValueError('unsafe expected file path')
        target=(root/str(rel)).resolve()
        if not target.is_relative_to(root):raise ValueError('file check escaped fixture directory')
        if text is None:
            if target.exists():errors.append(name+': unexpected output')
        elif not target.is_file() or target.read_bytes()!=text.encode('utf-8'):
            errors.append(name+': missing or wrong bytes')
    return not errors,errors
