# Windows C++：本机GCC与VS Code

## 你电脑上的实际配置

| 项目 | 路径/设置 |
|---|---|
| 工程与教材 | 仓库根目录 |
| 编译器 | D:/c++/MYSYS2/ucrt64/bin/g++.exe |
| C编译器/调试器 | 同目录gcc.exe / gdb.exe |
| 工作区 | workspaces/cpp.code-workspace |
| 编译标准 | C++17，-Wall -Wextra -Wpedantic -g -O0 |
| 调试输出 | 仓库根目录/build/active-program.exe |

这里用UCRT64 MinGW工具链。不要混入其他MinGW、MSVC的库或调试器来“碰碰运气”。目录名MYSYS2是本机实际拼法，不照网上默认C:/msys64改掉它。

## 一次确认工具

在PowerShell使用完整路径，避免PATH里另一个同名工具抢先：

```powershell
& 'D:/c++/MYSYS2/ucrt64/bin/g++.exe' --version
& 'D:/c++/MYSYS2/ucrt64/bin/gdb.exe' --version
Get-Command g++.exe -ErrorAction SilentlyContinue
```

前两项可执行但Get-Command找不到，通常是PATH未包含目录；本学习区任务使用完整路径，所以仍可构建。若手动修改用户PATH，需要新开终端。不要把整个include目录加进PATH。

## 打开、运行、输入

用专用工作区打开当前work.cpp，保存后选择当前文件运行任务。需要stdin时优先选读取input.txt的任务；多行输入按题目约定，不在输出中额外加提示语。

学习工具目前使用Codex配套Python的完整路径，不依赖你命令行里python实际指向哪个版本。下面第一行变量只是当前PowerShell终端里的简写：

```powershell
$learningPython = 'C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe'
Set-Location '仓库根目录'
& $learningPython tools/study.py run cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/reference.cpp --input cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/input.txt
& $learningPython tools/check-current.py cpp/主教材/章节学习/第03章 字符串类string/课后习题/第17题 支持负数与大位移的凯撒替换/work.cpp
```

参考输入与自己的作答不同，别把reference通过当work完成。换成独立Python时，需要同步任务command；使用图像示例的Python还需要相应依赖，不是随便换一个python.exe即可。

## F5配置为什么这样写

在.code-workspace中，预启动任务的实际核心为：

```json
{"label":"Windows: 编译当前文件供调试","type":"process","command":"C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe","args":["仓库根目录/tools/study.py","build","${file}","--active"]}
```

launch的program是固定active-program.exe，miDebuggerPath是上面的gdb.exe，preLaunchTask与label一致。普通编译仍分别输出到build下的源码对应目录。固定出口避免多根工作区的相对路径算错。

## 如果以后重装

按[VS Code官方MinGW教程](https://code.visualstudio.com/docs/cpp/config-mingw)配置MSYS2 UCRT64工具链、C/C++扩展和GDB；记录新安装目录，再统一改compilerPath、任务和调试器路径。本机已存在工具，不必为了对齐教程重装一遍。

先会用普通标准库和小工程，再接OpenCV或图形库。新目录里只写一个main可以用单文件构建；多文件工程要显式链接其他.cpp或使用构建系统，本区第2章10/11题由工具选择伴随源码。

## 新机器的最小配置顺序（当前电脑无需重复执行）

1. 安装Windows版VS Code与MSYS2，记录MSYS2安装目录。
2. 在MSYS2终端按官方教程安装UCRT64工具链：

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

3. 安装Microsoft C/C++扩展（ms-vscode.cpptools），配置对应UCRT64/bin的g++和gdb路径。
4. 若需要在普通终端直接输入g++，将该bin目录加入用户PATH，重新打开终端验证版本。
5. 在新建hello目录先手动编译一个小程序，再配置tasks与launch；不要先复制整套复杂图形工程配置。

此段是重建环境教程，不表示本轮运行了安装命令或更改了全局PATH。
