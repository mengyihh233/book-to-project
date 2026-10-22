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

# 本章任务：环境变量：查看、设置、导出与子进程继承

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'home_set=%s\n' "$([ -n "$HOME" ] && echo yes || echo no)"
export MY_VAR=hello
printf 'child_sees=%s\n' "$(bash -c 'printf "%s" "$MY_VAR"')"
printf 'path_set=%s\n' "$([ -n "$PATH" ] && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "导出变量能被子进程看到" "$(export MY_VAR=hello; bash -c "printf %s \"$MY_VAR\"")" "hello"
check "PATH 已设置且非空" "$([ -n "$PATH" ] && echo set)" "set"
check "HOME 环境变量存在" "$([ -n "$HOME" ] && echo set)" "set"
finish
