> 当前默认发行版已迁移为 **Ubuntu-22.04**，使用NAT与KDE桌面；旧Ubuntu26.04保留。先读[Ubuntu22桌面与迁移教程](Ubuntu22桌面与迁移教程.md)。本文历史命令若写`-d Ubuntu`，是旧系统；新系统明确使用`-d Ubuntu-22.04`。

# WSL：Linux下的C++与Shell开发

按最新安排恢复Linux C++开发入口。Windows和WSL共用仓库根目录源码，WSL中对应仓库根目录；不复制第二套教材与作答。

## 打开

桌面“重点学习（WSL Ubuntu）”，或工作台C++/Linux页面的“在 WSL Ubuntu 学习”，打开[远程工作区](../workspaces/focus-wsl.code-workspace)。左下角应显示WSL: Ubuntu，终端为Bash。

工作区包括Roberts20章、原书第1—3章、C++笔记与Linux章节/项目。Windows C++入口仍可使用；今后可以按实际需要选择Linux完成同一道题。

## 写一道C++题

1. 选中当前题work.cpp，保存。
2. “终端→运行任务→本题：运行作答”；文件输入用“本题：用样例输入运行”。
3. 用“本题：检查作答”检查自己的代码，保留字符串空格与题目退出码约定。
4. F9设断点，F5选“WSL: GDB调试当前C++”。预启动任务重新编译当前文件到~/.cache/book-learning/active-program，避免工作区根目录造成路径错误。

```bash
cd 仓库根目录
python3 tools/wsl-study.py run cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/work.cpp --input cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/input.txt
python3 tools/check-current.py cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/work.cpp
```

原书第2章的多文件库会选择对应实现；work.cpp链接自己的work库，不暗用答案。调试器为/usr/bin/gdb，编译器/usr/bin/g++，默认C++17。图形题输出SVG后可从Windows浏览器打开对应D盘文件。

## 环境、验收和缓存

Ubuntu、编译器、GDB、CMake、Ninja、Python、ShellCheck与已有OpenCV库一直保留。此前删的是生成缓存及旧报告，需要运行时会重建缓存，不需要恢复旧报告。

按需运行后台tools/check-wsl-cpp.py（按需维护）确认编译、输入、多文件链接与命令行GDB；这是环境烟雾检查，不是重新跑全部题。第2/3章完整参考验收也已恢复，只有你需要时运行；日常检查当前作答即可。

Windows.exe与Linux ELF分开生成，源码、work和学习状态共用。不要把构建缓存当作自己的作答目录，也不要混用Windows Python/GDB与Linux路径。

## Shell仍可使用

运行当前Shell、ShellCheck、环境检查任务保持可用，脚本保存LF。Windows Shell后端仍为WSL。连接异常先看wsl -l -v和“WSL: Show Log”，不要删除远程服务器或重装Ubuntu。

[统一环境手册](环境使用手册.md) · [VS Code官方WSL说明](https://code.visualstudio.com/docs/remote/wsl)。
