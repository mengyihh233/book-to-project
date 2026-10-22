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

# 本章任务：文件权限：解读 rwx 与权限位，用 test 判定访问能力

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

f=./probe.$$
: > "$f"
printf 'mode=%s\n' "$(stat -c '%a' "$f")"
printf 'symbolic=%s\n' "$(ls -l "$f" | cut -c1-10)"
printf 'readable=%s\n' "$([ -r "$f" ] && echo yes || echo no)"
printf 'writable=%s\n' "$([ -w "$f" ] && echo yes || echo no)"
printf 'umask=%s\n' "$(umask)"
chmod 444 "$f"
printf 'after_chmod_writable=%s\n' "$([ -w "$f" ] && echo yes || echo no)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "新建文件属主可读" "$(f=./pa.$$; : > "$f"; [ -r "$f" ] && echo yes)" "yes"
check "新建文件可写" "$(f=./pb.$$; : > "$f"; [ -w "$f" ] && echo yes)" "yes"
check "chmod 444 后不可写" "$(f=./pc.$$; : > "$f"; chmod 444 "$f"; [ -w "$f" ] || echo no)" "no"
check "权限位是八进制" "$(f=./pd.$$; : > "$f"; stat -c '%a' "$f" | grep -Eq '^[0-7]{3,4}$' && echo ok)" "ok"
check "umask 形如 0022" "$(umask | grep -Eq "^[0-7]{3,4}$" && echo ok)" "ok"
finish
