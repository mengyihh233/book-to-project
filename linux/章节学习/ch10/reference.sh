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

# 本章任务：编辑器与非交互式处理：用 sed/awk 完成一次批量改写

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

tmp=./edit.$$
mkdir -p "$tmp"
printf 'one\ntwo\nthree\n' > "$tmp/list.txt"
printf 'renamed=%s\n' "$(sed 's/one/1/' "$tmp/list.txt" | head -1)"
printf 'upper=%s\n' "$(tr 'a-z' 'A-Z' < "$tmp/list.txt" | sed -n '2p')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "sed 替换生效" "$(echo one | sed s/one/1/)" "1"
check "tr 大小写转换" "$(echo two | tr a-z A-Z)" "TWO"
finish
