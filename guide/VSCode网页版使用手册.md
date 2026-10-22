# 网页版VS Code使用手册

这里指电脑上已经接入Tailscale的私有网页版编辑器。它能编辑电脑文件、使用电脑终端；不是只打开一个vscode.dev网页后就自动获得你的本机编译环境。[官方Web说明](https://code.visualstudio.com/docs/remote/vscode-web)

## 从哪里进入最省事

日常从[学习工作台](https://lsy.tailaa8c77.ts.net:8443)打开一道题，再点“在网页VS Code作答”，这样文件夹就是该题。

需要看完整学习区时使用[完整工程编辑入口](https://lsy.tailaa8c77.ts.net:8444/?folder=%2FD%3A%2FBook-Learning)。只收藏8444根地址也可以，但不如工作台题目按钮明确。当前入口不需要额外登录GitHub；访问控制依靠已经连接的私有Tailscale网络。

## 看懂界面

| 名称 | 中文用途 | 常用动作 |
|---|---|---|
| Explorer | 资源管理器 | 打开work.cpp、input.txt和个人笔记 |
| Editor | 代码编辑区 | 输入、选择、查找、保存 |
| Terminal | 终端 | 执行编译、运行和检查命令 |
| Problems | 问题面板 | 查看语言插件产生的诊断；不代替编译结果 |
| Extensions | 扩展 | 管理当前网页版环境的扩展 |
| Command Palette | 命令面板 | 搜索编辑器动作；可从View菜单进入 |

平板横屏更宽。暂时不用右侧Chat时可关闭或收起该区域，把空间留给代码与终端；聊天功能不是运行C++的前提。网页编辑器已配暖白底、16号代码字和15号终端字；浏览器缩放会另行影响显示。

## 哪些文件由你修改

| 文件 | 用法 |
|---|---|
| work.cpp、work/main.cpp | 自己的程序，按每题README选择实际作答位 |
| input.txt或自己新建的输入文件 | 运行时的标准输入；保留原始样例也可另建my-input.txt |
| notes.md、work/notes.md | 自己的过程和失败记录 |
| README.md | 先读题意、协议和操作说明 |
| reference.cpp、lesson.h、solution.md | 参考答案，自己尝试后对照 |

第2章库题和第5章hist库题有多文件作答位置，以各题README为准；不要把整个目录的cpp随便一起编译，会遇到多个main或链接错参考库。

## 保存、查找与终端

外接键盘可用Ctrl+S保存、Ctrl+F查找、Ctrl+Shift+P打开命令面板。没有外接键盘时使用File → Save、Edit → Find、View → Command Palette；终端通过Terminal → New Terminal创建。快捷键需编辑器获得焦点，浏览器地址栏获得焦点时可能执行浏览器动作。

新建终端后看提示符：PS D:\...通常是Windows PowerShell；Linux提示符不完全固定，可输入pwd和uname -s确认。Windows和Linux的路径、命令、编译器不能混着用。

## 连通小实验：证明保存和编译确实生效

打开完整工程入口，找到cpp/主教材/运行产物/pad-link/main.cpp；这是独立环境小样例，不是原书作答。预期输出LEARNING_LINK_OK 5。

Windows终端：

```powershell
cd D:\Book-Learning
& 'C:\Users\lsy08\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' tools/study.py run cpp/主教材/运行产物/pad-link/main.cpp
```

Linux终端需要先从PowerShell进入WSL：

```powershell
wsl -d Ubuntu
```

然后在Linux运行：

```bash
cd 仓库根目录
python3 tools/wsl-study.py run cpp/主教材/运行产物/pad-link/main.cpp
```

看懂后可自己把2+3改成2+4，保存并重新运行，预期变为6；随后按自己的需要保留或改回。不要同时在电脑与平板改这个文件。Windows和WSL读同一份源码，但生成的可执行文件分别放在D盘build与Linux的~/.cache/book-learning。

## 原书题的运行与检查

以第5章12题为例，先在work.cpp独立实现。运行与检查不同：运行使用你给的输入，检查使用固定样例并比较输出。

Windows运行自己的输入：

```powershell
cd D:\Book-Learning
& 'C:\Users\lsy08\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' tools/study.py run cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/work.cpp --input cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/input.txt
```

Windows检查：

```powershell
& 'C:\Users\lsy08\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' tools/check-current.py cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/work.cpp
```

在WSL根目录下对应为：

```bash
cd 仓库根目录
python3 tools/wsl-study.py run cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/work.cpp --input cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/input.txt
python3 tools/check-current.py cpp/主教材/章节学习/第05章 集合类/课后习题/第12题 用栈逆序输出整数/work.cpp
```

input.txt会作为stdin传入，不是命令行参数文件。程序不结束时，先看题目是否需要0或空行终止；可在终端中止当前运行后修正输入，再运行。PowerShell不要照搬Bash的“程序 < input.txt”，现有工具使用--input。

## 文件夹、工作区、插件怎么区分

从题目进入时通常只打开一道题的文件夹，因此不会自动加载上层多文件夹工作区里的所有任务。此时先用本手册终端命令最清楚。若想使用已有Windows任务，可在File → Open Workspace from File（从文件打开工作区）选择D:\Book-Learning\workspaces\cpp.code-workspace，核对任务环境与当前源码。

网页版有自己的服务器扩展目录，桌面VS Code安装了某插件，不代表网页版已经安装；浏览器也有兼容性限制。只按学习需求启用扩展，不要为解决一个错误把桌面所有插件复制过来。工作区用于组织文件与配置，本身不保证隔离全部扩展。[扩展说明](https://code.visualstudio.com/docs/configure/extensions/extension-marketplace)

## Windows、WSL与调试边界

当前网页编辑器的扩展宿主在Windows，终端输入wsl -d Ubuntu只是进入Linux Shell。它不会自动把语言插件、调试器或整个编辑器变成WSL窗口。

本轮已验证Windows/WSL的编译运行与检查命令；没有把网页版F5图形调试当作已经配置成功。需要完整断点调试时，电脑桌面VS Code使用已有Windows或WSL工作区，见[环境使用手册](环境使用手册.md)。独立OpenCV/OpenGL窗口、ST-Link硬件操作也不直接显示在这个网页里。

## 遇到错误先分层

| 现象 | 先检查 |
|---|---|
| 文件标签有未保存标记 | 先保存再运行 |
| 找不到tools/practice.py | 终端cd到学习区根目录 |
| Windows找不到python | 使用本手册完整解释器路径 |
| Linux出现D:\路径错误 | 改用/mnt/d路径，确认已进入Ubuntu |
| undefined reference、重复main | 核对本题多文件工具入口，不手工通配编译整个目录 |
| 运行停着没输出 | 检查程序是否等stdin、终止符或循环条件 |
| 修改后结果不变 | 核对编辑与运行的是同一个work文件，重新编译 |
| 连接中断 | 先恢复Tailscale与电脑服务，保留未保存文字，不反复刷新 |

网页版配置与缓存位于D:\Book-Learning\.remote-vscode和.remote-vscode-cli。不要把这些当教材文件随意移动或清空。当前用户登录启动配置与恢复步骤见[联合学习说明](平板与电脑联合学习.md)。
