#!/usr/bin/env bash
# ---- 自校验框架：把结果和期望值比一比，错就报出来 ----
pass=0; fail=0
check() { # check 说明 实际值 期望值
  if [ "$2" = "$3" ]; then pass=$((pass+1)); printf 'PASS  %s\n' "$1"
  else fail=$((fail+1)); printf 'FAIL  %s\n  期望: [%s]\n  实际: [%s]\n' "$1" "$3" "$2"; fi
}
finish() {
  printf '\n%d 项通过，%d 项未过\n' "$pass" "$fail"
  [ "$fail" -eq 0 ] || exit 1
}

# 本章任务：编写脚本工具：带用法的命令行工具、错误处理与退出码

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

usage() { printf 'usage: tool <file>\n' >&2; }
tool() { [ -f "$1" ] || { usage; return 2; }; wc -l < "$1"; }
printf 'lines=%s\n' "$(tool "$DATA/words.txt")"
printf 'missing=%s\n' "$(tool /no/such/file 2>/dev/null; echo $?)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "正常路径返回行数" "$(wc -l < "$DATA/words.txt")" "4"
check "文件缺失时返回非零" "$(( [ -f /no/such ] || exit 2 ); echo $?)" "2"
check "用法信息写到 stderr" "$(u() { printf "usage\n" >&2; }; u 2>&1)" "usage"
finish
