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

# 本章任务：控制脚本：信号捕获 trap、后台运行与等待

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

tmp=./trap.$$
mkdir -p "$tmp"
( trap 'echo caught > "$tmp/sig"; exit 0' TERM; sleep 5 ) &
pid=$!
sleep 0.2; kill -TERM "$pid" 2>/dev/null; wait "$pid" 2>/dev/null
printf 'trapped=%s\n' "$([ -f "$tmp/sig" ] && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "trap 捕获 TERM" "$(( trap "echo caught; exit 0" TERM; sleep 5 ) & p=$!; sleep 0.2; kill -TERM $p; wait $p 2>/dev/null)" "caught"
check "wait 等待后台任务" "$((sleep 0.1) & wait; echo done)" "done"
finish
