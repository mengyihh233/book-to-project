> 当前默认发行版已迁移为 **Ubuntu-22.04**，使用NAT与KDE桌面；旧Ubuntu26.04保留。先读[Ubuntu22桌面与迁移教程](../Ubuntu22桌面与迁移教程.md)。本文历史命令若写`-d Ubuntu`，是旧系统；新系统明确使用`-d Ubuntu-22.04`。

# WSL与Linux C++：同一份源码，Linux本机构建

## 当前情况与打开方式

Windows上装VS Code，使用WSL扩展连接既有Ubuntu。桌面“重点学习（WSL Ubuntu）”或工作台C++页按钮已配置；左下角显示WSL: Ubuntu。Ubuntu用户mengyi，编译器/usr/bin/g++，调试器/usr/bin/gdb，默认C++17。

| Windows | WSL |
|---|---|
| 仓库根目录 | 仓库根目录 |
| PowerShell | Bash |
| g++.exe / gdb.exe | g++ / gdb |
| build/active-program.exe | ~/.cache/book-learning/active-program |
| 普通Windows程序 | Linux ELF程序 |

源码、work和学习进度共用。Ubuntu编译缓存按需重建，与教材不是一回事；不要把缓存目录当作唯一的作答保存位置。

## 环境检查

在Ubuntu终端执行：

```bash
uname -s
command -v g++ gdb cmake ninja python3 shellcheck
g++ --version
gdb --version
```

当前已安装这些工具。以后在一套全新Ubuntu上缺编译环境时，可参考发行版软件源安装build-essential和gdb；CMake/Ninja、ShellCheck按用途安装，不把“全部软件都装一次”当成第一步。

## 编译、输入与检查

```bash
cd 仓库根目录
python3 tools/wsl-study.py run cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/work.cpp --input cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/input.txt
python3 tools/check-current.py cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/work.cpp
```

VS Code对应任务：“本题：运行作答”“本题：用样例输入运行”“本题：检查作答”。下面的命令针对自己的work.cpp；参考实现不是个人判分入口。

## 调试

选中.cpp，F9断点，F5选择WSL配置。preLaunchTask运行wsl-study.py build 当前文件 --active，program指向${env:HOME}/.cache/book-learning/active-program，miDebuggerPath为/usr/bin/gdb。这三个必须一起属于Linux环境。

后台tools/check-wsl-cpp.py（按需维护）只验证代表性的编译、输入、多文件链接与GDB，不是每次把全书所有题重跑。完整章验收按需选择。

## 常见混淆

- 在Windows窗口里开Ubuntu终端，不等于C/C++扩展已经在WSL运行；检查远程标识和扩展安装位置。
- 不能把Windows的D:/g++.exe路径写成Linux compilerPath；也不能把Windows DLL拿去作为Linux.so链接。
- Linux文件名大小写敏感；include的大小写要与文件一致，脚本用LF。
- Bash读终端EOF可用Ctrl+D；不确定时使用input.txt。PowerShell与Bash的命令调用、重定向和变量语法不同。

以后迁移到真正Linux电脑，编译知识可沿用，但本机/mnt/d工作区路径需要改为实际工程路径，不能复制WSL快捷方式就认为完成迁移。

参考：[VS Code WSL](https://code.visualstudio.com/docs/remote/wsl)、[官方WSL入门](https://code.visualstudio.com/docs/remote/wsl-tutorial)。

## 新Ubuntu的最小配置顺序（已有环境不重复安装）

1. Windows保留VS Code客户端，安装WSL扩展，按官方WSL指引创建Ubuntu并记住Linux用户密码。
2. 在Ubuntu终端检查g++/gdb；确实缺少时再按[官方C++ WSL教程](https://code.visualstudio.com/docs/cpp/config-wsl)安装：

```bash
sudo apt-get update
sudo apt-get install build-essential gdb
```

3. 用VS Code连接Ubuntu，确认C/C++扩展安装在WSL侧。
4. 先在Linux原生目录写hello.cpp，g++ -g编译并运行，再接工作区和GDB。
5. 需要本学习区时，核对/mnt/d挂载与工作区路径；CMake/Ninja/ShellCheck按用途补充，不把其他机器的绝对路径直接照搬。

本机这些基本工具已在，以上为教学步骤，不是本轮执行的系统安装。

## Windows换行到WSL：CRLF与LF

同一份input.txt可能以Windows CRLF或Linux LF保存。Linux的std::getline只移除LF，可能留下CR，导致文件名变成sample.txt后跟一个不可见字符，或真正的空行被当作一个非空字符。VS Code右下角可查看/选择LF；只在确定是文本时转换，不对图片或可执行文件做换行转换。

第4章按行输入文件名/参数/标签，以及第5章分组读取和统计输入，已通过公共input_line.h兼容LF/CRLF：成功读行后移除一个行尾CR。正文中的孤立CR不作为这类行协议支持的内容。它仅处理输入协议，不改写磁盘源文件；第9/10题的真实文本转换仍按二进制读取、按题意保留CRLF，第8题的原始流处理规则独立。

新建练习可复用book_input::logicalLine，或自己写同样的规则，先明确文本格式。若从别的库直接getline，不要假定所有文件都已经由工具转换成LF。对Unix可执行脚本优先保留LF，避免解释器路径含CR。
