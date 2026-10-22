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

# 本章任务：认识 shell：输出 shell 名、内核名与当前用户，并判断自己跑在哪种 shell 里

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'shell=%s\n' "${BASH_VERSION%%(*}"
printf 'kernel=%s\n' "$(uname -s)"
printf 'user=%s\n' "$(id -un)"
printf 'is_bash=%s\n' "$([ -n "$BASH_VERSION" ] && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "输出包含 shell 名" "$(printf "%s" "$BASH_VERSION" | grep -q . && echo has)" "has"
check "内核名非空" "$(uname -s | grep -q . && echo has)" "has"
check "用户身份已取得" "$(id -un | grep -q . && echo has)" "has"
finish
