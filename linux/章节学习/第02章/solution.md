# LINUX-L02 参考思路

printf可能是内建命令；cd必须改变当前shell目录，因此通常是内建。管道末端head可能提前关闭输出，学习时注意pipefail行为。

先看思路，再打开reference.sh。可用运行任务执行参考脚本；产生的文件只放sandbox。
