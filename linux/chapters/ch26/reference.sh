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

# 本章任务：综合小工具：把学过的命令组合成一个可复用脚本

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

report() {
  printf '总人数=%s\n' "$(awk -F, 'NR>1' "$DATA/scores.csv" | wc -l)"
  printf '平均分=%s\n' "$(awk -F, 'NR>1{s+=$2; n++} END{printf "%.1f", s/n}' "$DATA/scores.csv")"
  printf '最高分=%s\n' "$(awk -F, 'NR>1{if($2>m)m=$2} END{print m}' "$DATA/scores.csv")"
}
report
printf 'words=%s\n' "$(wc -l < "$DATA/words.txt")"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "统计人数" "$(awk -F, "NR>1" "$DATA/scores.csv" | wc -l)" "3"
check "平均分一位小数" "$(awk -F, "NR>1{s+=\$2; n++} END{printf \"%.1f\", s/n}" "$DATA/scores.csv")" "85.0"
check "最高分" "$(awk -F, "NR>1{if(\$2>m)m=\$2} END{print m}" "$DATA/scores.csv")" "90"
finish
