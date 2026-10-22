#!/usr/bin/env bash
# 只读图像数据集盘点。--null输出NUL分隔清单，摘要写stderr。
set -euo pipefail
if (( $# < 1 || $# > 2 )); then printf 'usage: dataset-audit DIRECTORY [--null]\n' >&2; exit 2; fi
root=$1; mode=${2:-report}
if [[ ! -d "$root" || ( "$mode" != report && "$mode" != --null ) ]]; then printf 'invalid directory or option\n' >&2; exit 2; fi
cd -P -- "$root"
root=$PWD
images=0; others=0; traversal=ERROR
while IFS= read -r -d '' file; do
    if [[ -z "$file" ]]; then IFS= read -r -d '' traversal || true; break; fi
    name=${file,,}
    case "$name" in
        *.png|*.jpg|*.jpeg|*.bmp)
            images=$((images+1))
            if [[ "$mode" == --null ]]; then printf '%s\0' "$file"; else printf 'IMAGE %q\n' "$file"; fi
            ;;
        *) others=$((others+1));;
    esac
done < <(if find "$root" -type f -print0; then printf '\0OK\0'; else printf '\0ERROR\0'; fi)
if [[ "$traversal" != OK ]]; then printf 'directory traversal failed; discard partial listing\n' >&2; exit 2; fi
if [[ "$mode" == --null ]]; then printf 'images=%d others=%d\n' "$images" "$others" >&2
else printf 'images=%d others=%d\n' "$images" "$others"; fi
