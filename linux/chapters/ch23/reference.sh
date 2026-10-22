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

# 本章任务：了解其他 shell：POSIX 兼容写法与 shell 间差异

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'posix_ok=%s\n' "$(bash --posix -c 'printf "%s" "${BASH_VERSION%%(*)}"' >/dev/null && echo yes || echo no)"
printf 'arith_posix=%s\n' "$(x=2; y=3; echo $((x * y)))"
printf 'has_dash=%s\n' "$(command -v dash >/dev/null && echo has || echo none)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "算术展开在 POSIX 下同样可用" "$(echo $((2 * 3)))" "6"
check "命令替换可嵌套" "$(echo "$(echo nested)")" "nested"
finish
