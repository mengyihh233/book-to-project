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

# 本章任务：创建函数：参数传递、返回值与局部变量

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

add() { local a=$1 b=$2; echo $((a + b)); }
printf 'add=%s\n' "$(add 3 4)"
greet() { printf 'hello %s\n' "${1:-world}"; }
printf 'default=%s\n' "$(greet)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "函数返回计算结果" "$(add() { echo $(($1 + $2)); }; add 3 4)" "7"
check "参数默认值生效" "$(f() { echo "${1:-fallback}"; }; f)" "fallback"
check "local 不外泄" "$(f() { local v=inner; }; v=outer; f; echo $v)" "outer"
finish
