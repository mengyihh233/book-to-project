#!/usr/bin/env bash
# 【本题说明开始】
# Linux第26章
#
# 题目与要求：
# 综合小工具：把学过的命令组合成一个可复用脚本
#
# 写在哪里：只编辑本文件中的自己的实现；不要复制参考答案覆盖。
# 怎么做：先手算样例，再写实现，最后检查正常、边界和错误情况。
# 怎么检查：脚本末尾check/finish是本章自检；不是独立的完整评分器。
#
# 写在哪里：# TODO下面的作答区，按提示替换true占位；保留期望值和检查框架。
# 部分check只检查当前环境，空实现也可能显示通过；必须同时完成上面的任务。
# 输入/文件：按README使用DATA样例，输出在工具提供的沙箱，不在原数据上试删除。
# 完整题目与文本格式：README.md。
# 【本题说明结束】
#
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

# 本章任务：综合小工具：把学过的命令组合成一个可复用脚本
# 在下面写出你自己的实现，然后用同一套 check 验收。
# 卡住时对照 reference.sh，但先自己写完再看。

export DATA=${DATA:-/mnt/d/Book-Learning/linux/data}

# TODO: 在这里写你的实现（先删掉下面这行占位）
true

# ---- 验收：换成你自己的实现，期望值保持不变 ----
check "统计人数" "$(awk -F, "NR>1" "$DATA/scores.csv" | wc -l)" "3"
check "平均分一位小数" "$(awk -F, "NR>1{s+=\$2; n++} END{printf \"%.1f\", s/n}" "$DATA/scores.csv")" "85.0"
check "最高分" "$(awk -F, "NR>1{if(\$2>m)m=\$2} END{print m}" "$DATA/scores.csv")" "90"
finish
