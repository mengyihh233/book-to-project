#!/usr/bin/env bash
set -euo pipefail
project_dir=$(CDPATH='' cd -- "$(dirname -- "$0")" && pwd)
input=${1:-"$project_dir/sample.csv"}
if [[ $# -gt 1 || ! -f "$input" ]]; then
    printf '用法：bash reference.sh [成绩CSV路径]\n' >&2
    exit 2
fi
# 数据只读；报告写到标准输出，由调用者决定是否保存。
LC_ALL=C awk -f "$project_dir/report.awk" "$input"
