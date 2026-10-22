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

# 本章任务：文件系统：查看挂载点、磁盘占用与 inode 使用

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

printf 'root_fs=%s\n' "$(df -P / | awk 'NR==2{print $1}')"
printf 'root_used_nonzero=%s\n' "$(df -P / | awk 'NR==2{exit !($3>0)}' && echo yes || echo no)"
printf 'inodes=%s\n' "$(df -i / | awk 'NR==2{print $2}')"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "/ 已挂载且有用量" "$(df -P / | awk "NR==2{exit !(\$3>0)}" && echo yes)" "yes"
check "inode 总数可读" "$(df -i / | awk "NR==2{print \$2}" | grep -q . && echo has)" "has"
finish
