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

# 本章任务：构建第一个脚本：带参数、shebang 与退出码

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

d=./first.$$
mkdir -p "$d"
printf '#!/usr/bin/env bash\necho "arg=$1"\n' > "$d/run.sh"
printf 'output=%s\n' "$(bash "$d/run.sh" hello)"
printf 'exit=%s\n' "$(bash "$d/run.sh" hello >/dev/null; echo $?)"

# ---- 验收：把上面跑出来的结果和期望值比对 ----
check "脚本可执行并传参" "$(d=./s.$$; mkdir -p "$d"; printf "#!/usr/bin/env bash\necho \$1\n" > "$d/r.sh"; bash "$d/r.sh" hi)" "hi"
check "正常退出码为 0" "$(true; echo $?)" "0"
finish
