# Ubuntu 内的 VS Code：打开、练习和调试

更新：2026-10-21。Ubuntu-22.04 内已安装微软官方 VS Code **1.142.0**，中文界面、浅色主题、C/C++ 扩展已配置。原 Windows VS Code 继续保留。[实际界面](../workbench/verification/ubuntu22/vscode-linux.png) · [Ubuntu 桌面与迁移教程](Ubuntu22桌面与迁移教程.md)

## 先打开这一个入口

1. Windows 桌面双击 **Ubuntu 22.04 桌面**。
2. 如出现 xrdp 登录，选择 **Xorg**，用户 **mengyi**，输入原 Linux 密码。
3. 进入 KDE 后，双击桌面的 **VS Code Linux 学习工作区**；应用菜单也能搜到同名入口。

它会打开 `仓库根目录/workspaces/focus-wsl.code-workspace`。第一次询问是否信任时，确认路径确为自己的这份学习目录，再信任此工作区，才能运行任务。无需关闭全局工作区信任功能。

也可在 Ubuntu 的 Konsole 终端执行：

```bash
code-linux 仓库根目录/workspaces/focus-wsl.code-workspace
```

`code-linux .` 打开当前目录，适合自己的新 Linux 项目；**现有学习区优先打开上面的 focus-wsl 工作区**，其中已配好 Linux 任务。普通 `cpp.code-workspace` 和部分文件夹级配置使用 Windows 工具路径，不能直接当作 Linux 配置。

## 每次练习只走一条流程

在左侧进入当前章节，先读 README，再打开自己的 `work` 源码。库函数练习从[分组入口](../cpp/主教材/常用库练习/README.md)选正在学的一组即可。

保存当前 `.cpp` 后，按 **Ctrl+Shift+P**，搜索“运行任务”，选择：

| 想做什么 | 选择哪个任务 |
|---|---|
| 编译并运行当前文件 | **本题：运行作答** |
| 使用同目录的 input.txt 输入 | **本题：用样例输入运行** |
| 检查已配套的原书作答 | **本题：检查作答** |
| 排查编译、调试或路径配置 | **WSL: C++开发链路检查** |
| 检查整体 Linux 学习环境 | **WSL: 接入环境综合验收** |

“当前原书作答检查”只用于已有题号登记的原书 `work` 文件；章内主练习、API 分组或自己的新文件用编译运行与题目给出的核对方式。不要为看见绿色结果而直接运行参考并登记自己完成。

程序需要键盘输入时，点击下方任务终端再输入；自动重复实验用同目录 `input.txt` 更方便。未完成的模板会明确提示或返回非零，这是待作答状态，通常不代表环境坏了。

## 遇到问题，用断点看一次

1. 保持要调试的 `.cpp` 为当前编辑文件，保存它。
2. 在 `main` 内有效代码的行号左侧点一个红点。
3. 左侧“运行和调试”选择 **WSL: GDB调试当前C++**，按 **F5**。
4. 停住后看局部变量；**F10** 单步越过，**F11** 进入自己的函数，**Shift+F5** 结束。

调试会先运行匹配的构建任务，使用 `/usr/bin/g++` 和 `/usr/bin/gdb`。当前调试出口是 `~/.cache/book-learning/active-program`；源码仍在 D 盘。不要同时在两个窗口启动这一个共用调试出口。

本轮已实测 Linux ELF 编译、文件输入、GDB 的 main 断点、多文件链接、工作区路径与任务匹配，**7/7 通过**；整体 Linux 接入检查 **11/11 通过**。真实中文图形窗口已绘制并截图；没有替你操作真实 RDP 密码登录或 GUI F5 按钮。

## 两个 VS Code 入口怎样选

| 入口 | 界面在哪里 | 代码和编译器在哪里 |
|---|---|---|
| KDE 的 **VS Code Linux 学习工作区** | Ubuntu 桌面内 | 共享 D 盘源码 + Ubuntu GCC/GDB |
| Windows 桌面的 **Ubuntu 22.04 学习 VS Code** | Windows 窗口，左下角 WSL: Ubuntu-22.04 | 同一份共享源码 + 同一个 Ubuntu GCC/GDB |

今天想在完整 Ubuntu 桌面里操作，就用第一个。想直接在 Windows 桌面写 Linux C++，就用第二个。两者的扩展与界面设置分别保存；不用把所有 Windows 插件复制到 Linux。Ubuntu 原生 VS Code 不需要再装 WSL 扩展。

当前 Ubuntu 用户只加装 **中文语言包** 和 **C/C++** 两项扩展，内置 Git 与终端可直接用。Linux Git 已复用 Windows GitHub 登录；这与 VS Code 的设置同步账号不同，需要同步时再在编辑器里自行浏览器授权。[GitHub 与文件交互说明](Ubuntu22桌面与迁移教程.md)

## 常用设置在哪里

- **Ctrl+,** 打开设置：字号、自动保存等按习惯调整。当前字号 15、关闭缩略图，浅色主题为 Default Light Modern。
- **Ctrl+Shift+P → Configure Display Language**：当前为 `zh-cn`，改语言后重启窗口。
- 用户设置在 `~/.config/Code/User/settings.json`；启动参数在 `~/.vscode/argv.json`；本次已设置中文和关闭硬件加速，避免远程 X11 显示异常。
- 当前工作区任务和调试配置在 `仓库根目录/workspaces/focus-wsl.code-workspace`，通常不用再抄一份 `.vscode` 配置。

遇到黑屏或空白先关闭自己的这个窗口，再从 `code-linux` 入口打开；它固定使用 X11 并关闭 GPU 加速。遇到 `python.exe`、`gdb.exe` 路径报错，先检查是否打开了正确的 focus-wsl 工作区。不要使用 `sudo code`。

系统更新时可通过 Ubuntu 的微软 APT 源更新 `code` 软件包；无需每次重新下载或配置环境。首次 Linux 原生安装参照[微软 Linux 安装说明](https://code.visualstudio.com/docs/setup/linux)，Windows 远程入口参照[微软 WSL 开发说明](https://code.visualstudio.com/docs/remote/wsl)，参数参照[官方 CLI 文档](https://code.visualstudio.com/docs/configure/command-line)。

[在 Ubuntu 浏览器打开学习工作台](Ubuntu工作台与浏览器说明.md)：KDE 点“学习工作台（Ubuntu浏览器）”，或 Konsole 输入 learning-workbench；共用原资料和进度。

## 多文件项目与CMake

[Linux CMake教学](Linux-CMake教学.md)使用同一有理数类项目讲构建、库、测试和Debug。工作区新增4个CMake任务及专用GDB配置；此项目不要使用普通单文件任务。自己的核心实现仍只有一份work/rational.cpp。
