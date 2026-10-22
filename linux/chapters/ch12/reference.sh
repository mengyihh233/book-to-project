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

# 本章任务：结构化命令：if/then、test 与退出码判断

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

score=85
if [ "$score" -ge 90 ]; then grade=A
elif [ "$score" -ge 80 ]; then grade=B
else grade=C; fi
printf 'grade=%s\n' "$grade"
printf 'empty_test=%s\n' "$([ -z "" ] && echo empty || echo not)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "85 分判为 B" "$(s=85; if [ $s -ge 90 ]; then g=A; elif [ $s -ge 80 ]; then g=B; else g=C; fi; echo $g)" "B"
check "test -z 判空串" "$([ -z "" ] && echo empty)" "empty"
finish
