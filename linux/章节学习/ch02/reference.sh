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

# 本章任务：用 type、command -v、help 区分内建命令与外部命令

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'builtin=%s\n' "$(type -t cd)"
printf 'external=%s\n' "$(type -t ls)"
printf 'has_cd_help=%s\n' "$(help cd >/dev/null 2>&1 && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "cd 是内建命令" "$(type -t cd)" "builtin"
check "ls 是外部命令" "$(type -t ls)" "file"
check "help 只对内置命令有效" "$(help cd >/dev/null 2>&1 && echo ok)" "ok"
finish
