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

# 本章任务：理解 shell 执行方式：后台任务、子 shell 与变量作用域

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

x=parent
printf 'subshell=%s\n' "$(x=child; printf "%s" "$x")"
printf 'parent=%s\n' "$x"
printf 'background=%s\n' "$(sleep 0.1 & echo started; wait)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "子 shell 改不了父 shell" "$(x=parent; ( x=child ); echo "$x")" "parent"
check "后台任务可等待" "$((sleep 0.1 &) && echo ran)" "ran"
finish
