"""Resolve old C++ learning URLs without duplicate folders or source files."""
import json
from functools import lru_cache
from pathlib import Path
from urllib.parse import quote, unquote

ROOT = Path(__file__).resolve().parents[1]

@lru_cache(maxsize=1)
def _rules():
    rules = json.loads((ROOT / 'tools/cpp-path-map.json').read_text(encoding='utf-8'))
    return sorted(rules.items(), key=lambda item: -len(item[0]))

def current_path(value):
    if not isinstance(value, str):
        return value
    for old, new in _rules():
        if value == old or value.startswith(old + '/'):
            return new + value[len(old):]
    return value

def current_links(value):
    if isinstance(value, dict):
        return {key: current_links(item) for key, item in value.items()}
    if isinstance(value, list):
        return [current_links(item) for item in value]
    if isinstance(value, str):
        if '?doc=' in value:
            start, path = value.split('?doc=', 1)
            return start + '?doc=' + quote(current_path(unquote(path)), safe='')
        return current_path(value)
    return value
