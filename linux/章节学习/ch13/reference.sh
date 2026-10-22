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

# 本章任务：更多结构化命令：case、for 与算术展开

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'loop=%s\n' "$(for i in 1 2 3; do printf '%s' "$i"; done)"
printf 'arith=%s\n' "$((3 * 4 + 1))"
case abc in a*) printf 'case=matched\n' ;; *) printf 'case=no\n' ;; esac

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "算术展开正确" "$(echo $((3 * 4 + 1)))" "13"
check "for 循环累加字符串" "$(for i in 1 2 3; do printf "%s" "$i"; done)" "123"
check "case 前缀匹配" "$(case abc in a*) echo matched ;; esac)" "matched"
finish
