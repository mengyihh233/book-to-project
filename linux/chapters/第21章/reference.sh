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

# 本章任务：sed 进阶：寻址、保持空间与多命令编辑

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'range=%s\n' "$(printf '1\n2\n3\n4\n' | sed -n '2,3p' | tr '\n' ' ')"
printf 'delete=%s\n' "$(printf 'keep\ndrop\nkeep\n' | sed '/drop/d' | tr '\n' ' ')"
printf 'append=%s\n' "$(printf 'a\n' | sed 'a b' | tr '\n' ' ')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "地址范围 2,3" "$(printf "1\n2\n3\n4\n" | sed -n 2,3p | tr "\n" " ")" "2 3 "
check "按模式删除行" "$(printf "keep\ndrop\nkeep\n" | sed /drop/d | tr "\n" " ")" "keep keep "
check "sed 追加行" "$(printf "a\n" | sed "a b" | tr "\n" " ")" "a b "
finish
