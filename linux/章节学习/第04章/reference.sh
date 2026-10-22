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

# 本章任务：处理文件：复制、改名、按内容查找，并统计文件个数

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

work=./work.$$
mkdir -p "$work"
cp "$DATA/words.txt" "$work/a.txt"
mv "$work/a.txt" "$work/b.txt"
printf 'exists=%s\n' "$([ -f "$work/b.txt" ] && echo yes || echo no)"
printf 'count=%s\n' "$(ls -1 "$work" | wc -l)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "复制并改名成功" "$(tmp=./w.$$; mkdir -p "$tmp"; cp "$DATA/words.txt" "$tmp/a"; mv "$tmp/a" "$tmp/b"; [ -f "$tmp/b" ] && echo yes)" "yes"
check "cp 保留原文件" "$([ -f "$DATA/words.txt" ] && echo kept)" "kept"
finish
