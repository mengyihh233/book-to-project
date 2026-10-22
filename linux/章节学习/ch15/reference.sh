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

# 本章任务：呈现数据：对齐输出、制表符与数字格式化

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf '%-8s|%5d\n' name 42
printf 'float=%.2f\n' 3.14159
printf 'tabbed=%s\n' "$(printf 'a\tb' | cat -T)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "printf 宽度对齐" "$(printf "%-8s|%5d" name 42)" "name    |   42"
check "保留两位小数" "$(printf "%.2f" 3.14159)" "3.14"
check "制表符可显示" "$(printf "a\tb" | cat -T)" "a^Ib"
finish
