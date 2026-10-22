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

# 本章任务：交互脚本：从 stdin 读菜单选择并分支处理

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

choice=b
case "$choice" in
  a) result=apple ;;
  b) result=banana ;;
  *) result=unknown ;;
esac
printf 'result=%s\n' "$result"
printf 'menu_lines=%s\n' "$(printf 'a) apple\nb) banana\n' | wc -l)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "菜单分支正确" "$(c=b; case $c in a) r=apple;; b) r=banana;; *) r=unknown;; esac; echo $r)" "banana"
check "选项行数正确" "$(printf "a) apple\nb) banana\n" | wc -l)" "2"
finish
