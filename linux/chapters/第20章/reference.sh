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

# 本章任务：正则表达式：字符类、锚点与分组

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'digit=%s\n' "$(printf 'abc123\n' | grep -o '[0-9]\+' | head -1)"
printf 'anchor=%s\n' "$(printf 'start here\n' | grep -c '^start')"
printf 'email=%s\n' "$(printf 'a@b.com\n' | grep -Ec '[a-z]+@[a-z]+\.[a-z]+')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "匹配数字片段" "$(echo abc123 | grep -o "[0-9]\+")" "123"
check "行首锚点生效" "$(echo start here | grep -c "^start")" "1"
check "邮箱模式匹配" "$(echo a@b.com | grep -Ec "[a-z]+@[a-z]+\.[a-z]+")" "1"
finish
