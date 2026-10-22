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

# 本章任务：文件与目录基础：列出文件、按行统计、确认可读

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'lines=%s\n' "$(wc -l < "$DATA/words.txt")"
printf 'bytes=%s\n' "$(wc -c < "$DATA/words.txt")"
printf 'readable=%s\n' "$([ -r "$DATA/words.txt" ] && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "words.txt 有 4 行" "$(wc -l < "$DATA/words.txt")" "4"
check "文件可读" "$([ -r "$DATA/words.txt" ] && echo yes)" "yes"
finish
