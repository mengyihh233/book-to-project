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

# 本章任务：初识 sed 与 gawk：行选取、替换与字段提取

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'lines=%s\n' "$(printf 'a\nb\nc\n' | sed -n '2p')"
printf 'field=%s\n' "$(printf 'x y z\n' | awk '{print $2}')"
printf 'replaced=%s\n' "$(printf 'foo bar\n' | sed 's/foo/baz/')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "sed 取第 2 行" "$(printf "a\nb\nc\n" | sed -n 2p)" "b"
check "awk 取第 2 字段" "$(printf "x y z\n" | awk "{print \$2}")" "y"
check "sed 替换首个匹配" "$(echo foo bar | sed s/foo/baz/)" "baz bar"
finish
