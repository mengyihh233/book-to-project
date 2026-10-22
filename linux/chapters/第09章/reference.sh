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

# 本章任务：软件管理：用命令查询已安装程序与版本信息（不实际安装）

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'bash_version=%s\n' "${BASH_VERSION%%(*}"
printf 'tools_ok=%s\n' "$(for t in ls grep awk; do command -v "$t" >/dev/null || exit 1; done; echo yes)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "常用工具齐备" "$(for t in ls grep awk sed; do command -v "$t" >/dev/null || exit 1; done; echo yes)" "yes"
check "bash 版本号格式正确" "$(echo "${BASH_VERSION%%(*}" | grep -Eq "^[0-9]+\.[0-9]+\.[0-9]+" && echo ok)" "ok"
finish
