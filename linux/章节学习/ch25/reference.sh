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

# 本章任务：与数据交互：解析 CSV、JSON 字段与生成报表

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'names=%s\n' "$(awk -F, 'NR>1{printf "%s ", $1}' "$DATA/scores.csv")"
printf 'avg=%s\n' "$(awk -F, 'NR>1{s+=$2; n++} END{printf "%.2f", s/n}' "$DATA/scores.csv")"
printf 'course=%s\n' "$(grep -o '"course": *"[^"]*"' "$DATA/course.json" | cut -d'"' -f4)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "提取姓名列" "$(awk -F, "NR>1{printf \"%s \", \$1}" "$DATA/scores.csv")" "alice bob carol "
check "平均分保留两位" "$(awk -F, "NR>1{s+=\$2; n++} END{printf \"%.2f\", s/n}" "$DATA/scores.csv")" "85.00"
check "JSON 字段可提取" "$(grep -o "\"course\": *\"[^\"]*\"" "$DATA/course.json" | cut -d"\"" -f4)" "Linux and Shell"
finish
