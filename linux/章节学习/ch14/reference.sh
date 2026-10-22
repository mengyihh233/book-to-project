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

# 本章任务：处理用户输入：read、getopts 与位置参数

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'input=%s\n' "$(printf 'hello world\n' | { read -r a b; echo "$a-$b"; })"
set -- one two three
printf 'shifted=%s\n' "$(shift; echo "$1")"
printf 'count=%s\n' "$#"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "read 拆分会话字段" "$(printf "a b\n" | { read -r x y; echo "$x-$y"; })" "a-b"
check "shift 后第一个参数" "$(set -- one two; shift; echo "$1")" "two"
check "$# 统计参数个数" "$(set -- a b c; echo $#)" "3"
finish
