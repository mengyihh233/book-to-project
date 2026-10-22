"""原书阅读器：只服务固定这一本 PDF 的页图与已发布原文。

安全边界：
- 只有一本白名单 PDF（books/cpp-roberts.pdf），页码严格 1..659。
- 图像按需渲染，落在 build/cpp-reader，不预生成全书大图。
- 原文与图示只能取自 cpp/roberts/original 下已登记的文件，文件名走白名单正则。
- 不提供任意路径读取、命令执行或写文件接口。
"""
import json
import re
import threading
from pathlib import Path
from path_compat import current_links

ROOT = Path(__file__).resolve().parents[1]
BOOK = ROOT / 'books/cpp-roberts.pdf'
DATA = ROOT / 'cpp/roberts/original'
CACHE = ROOT / 'build/cpp-reader'
TOTAL_PAGES = 659
MIN_SCALE, MAX_SCALE = 1.0, 4.0
DEFAULT_SCALE = 2.4

_RENDER_LOCK = threading.Lock()
_FIGURE_RE = re.compile(r'^\d{4}\.fig-[a-z0-9-]+\.png$')


def _read_json(path, fallback):
    try:
        return json.loads(path.read_text(encoding='utf-8'))
    except (OSError, ValueError):
        return fallback


def manifest():
    """阅读器需要的目录：页码范围、每页状态、小节与关联任务。"""
    data = _read_json(DATA / 'reader.json', None)
    if not data:
        return dict(ready=False, pages=[], sections=[], links={}, message='原书阅读数据尚未发布')
    data['ready'] = True
    data = current_links(data)
    # OCR publishing may still use the former folder names. Supply the current
    # student entry from the live tree without editing the transcribed material.
    for chapter in data.get('chapter_links', {}).values():
        main = chapter.get('main') or {}
        folder = main.get('folder')
        if folder:
            candidate = Path(folder) / '我的作答/main.cpp'
            if (ROOT / candidate).is_file():
                main['work'] = candidate.as_posix()
    return data


def check_page(page):
    if not isinstance(page, int) or isinstance(page, bool):
        raise ValueError('页码必须是整数')
    if not 1 <= page <= TOTAL_PAGES:
        raise ValueError('页码超出 1..%d' % TOTAL_PAGES)
    return page


def _source_stamp():
    stat = BOOK.stat()
    return '%x-%x' % (stat.st_mtime_ns, stat.st_size)


def _cache_dir():
    CACHE.mkdir(parents=True, exist_ok=True)
    stamp_file = CACHE / 'source.json'
    current = _source_stamp()
    if _read_json(stamp_file, {}).get('stamp') != current:
        for old in CACHE.glob('page-*.png'):
            try:
                old.unlink()
            except OSError:
                pass
        stamp_file.write_text(json.dumps(dict(stamp=current, book=BOOK.name)), encoding='utf-8')
    return CACHE


def page_image(page, scale=DEFAULT_SCALE):
    """渲染并缓存一页；返回 (path, width, height)。页码与倍率均已校验。"""
    check_page(page)
    try:
        scale = float(scale)
    except (TypeError, ValueError):
        scale = DEFAULT_SCALE
    scale = round(min(MAX_SCALE, max(MIN_SCALE, scale)), 2)
    target = _cache_dir() / ('page-%04d@%.2f.png' % (page, scale))
    if target.exists() and target.stat().st_size > 0:
        return target, page, scale
    with _RENDER_LOCK:
        if target.exists() and target.stat().st_size > 0:
            return target, page, scale
        import pypdfium2 as pdfium
        document = pdfium.PdfDocument(str(BOOK))
        try:
            bitmap = document[page - 1].render(scale=scale)
            image = bitmap.to_pil()
            temp = target.with_suffix('.tmp')
            image.save(temp, format='PNG', optimize=True)
            temp.replace(target)
        finally:
            document.close()
    return target, page, scale


def figure_path(name):
    """只允许已登记图示文件名；解析后仍须落在 DATA/figures 内。"""
    if not isinstance(name, str) or not _FIGURE_RE.match(name):
        raise ValueError('图示名不在白名单内')
    path = (DATA / 'figures' / name).resolve()
    if not path.is_file() or path.parent != (DATA / 'figures').resolve():
        raise ValueError('图示不存在')
    return path


def page_text(page):
    """已发布页的原文与识别层；未发布页明确返回空，不用导读冒充原文。"""
    check_page(page)
    meta = _read_json(DATA / 'pages' / ('%04d.meta.json' % page), None)
    if not meta:
        return dict(page=page, published=False)
    reviewed = meta.get('reviewed')
    text = ''
    if reviewed:
        candidate = (DATA / reviewed).resolve()
        if candidate.is_file() and DATA.resolve() in candidate.parents:
            text = candidate.read_text(encoding='utf-8')
    return dict(page=page, published=True, meta=meta, reviewed=text)


def send_png(handler, path):
    data = path.read_bytes()
    handler.send_response(200)
    handler.send_header('Content-Type', 'image/png')
    handler.send_header('Content-Length', str(len(data)))
    handler.send_header('Cache-Control', 'private, max-age=86400')
    handler.end_headers()
    try:
        handler.wfile.write(data)
    except (BrokenPipeError, ConnectionResetError, ConnectionAbortedError):
        pass
