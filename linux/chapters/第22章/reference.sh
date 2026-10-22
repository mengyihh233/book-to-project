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

# 本章任务：gawk 进阶：数组、聚合与自定义函数

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'sum=%s\n' "$(printf '10\n20\n30\n' | awk '{s+=$1} END{print s}')"
printf 'count=%s\n' "$(printf 'a\nb\nc\n' | awk 'END{print NR}')"
printf 'max=%s\n' "$(printf '3\n9\n5\n' | awk 'NR==1||$1>m{m=$1} END{print m}')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "累加求和" "$(printf "10\n20\n30\n" | awk "{s+=\$1} END{print s}")" "60"
check "统计行数 NR" "$(printf "a\nb\nc\n" | awk "END{print NR}")" "3"
check "求最大值" "$(printf "3\n9\n5\n" | awk "NR==1||\$1>m{m=\$1} END{print m}")" "9"
finish
