# 环境配置教程：先理解，再操作

这套教程以你电脑的实际目录和学习工具为例。不是让你重新安装全部软件；先会判断“现在在哪个环境、哪个阶段出了问题”。本机路径是当前配置，换电脑或移动安装目录后要重新核对。

## 建议阅读顺序

| 顺序 | 教程 | 解决什么疑问 |
|---|---|---|
| 1 | [配置的共同原理](01-共同原理.md) | 编译器、链接器、调试器、库和PATH分别干什么 |
| 2 | [VS Code配置关系](02-VSCode配置.md) | 工作区、settings、tasks、launch、插件与配置文件 |
| 3 | [Windows C++](03-Windows-Cpp.md) | 本机GCC、输入、构建与F5 |
| 4 | [WSL / Linux C++与Shell](04-WSL-Linux.md) | 远程窗口、Linux编译、调试、路径与迁移 |
| 5 | [OpenCV](05-OpenCV.md) | include、链接、DLL、Windows和Linux库的区别 |
| 6 | [OpenGL / 图形学 / GUI](06-图形与GUI.md) | 哪些需要GPU，哪些只需普通C/C++ |
| 7 | [STM32F103 + ST-Link](07-STM32.md) | ARM交叉编译、烧录、调试与CubeMX的分工 |
| 8 | [其他教材、Python和工作台](08-其他与工作台.md) | 哪些示例是概念模拟，网页是否需要npm |
| 9 | [平板联动快速上手](../平板联动快速上手.md) | 从Tailscale连接、选题、保存到复盘 |
| 10 | [网页版VS Code手册](../VSCode网页版使用手册.md) | 文件、菜单、终端、运行、工作区和插件 |

## 当前环境怎么选

| 目标 | 使用环境 | 主要工具 |
|---|---|---|
| Windows普通C++程序 | VS Code本地窗口 | UCRT64 g++、GDB |
| Linux普通C++程序 | VS Code WSL Ubuntu窗口 | /usr/bin/g++、/usr/bin/gdb |
| Linux/Shell实验 | WSL | Bash、ShellCheck、Python |
| 当前完整OpenCV / OpenGL项目 | Windows | 现有配套库及运行工具 |
| STM32裸机程序 | 独立STM32工作区，当前用Windows | arm-none-eabi工具链、烧录器、探头 |

Windows和WSL共用仓库根目录源码，构建产物分开。写C++不等于必须用Windows，也不等于所有硬件、GUI和库都能直接跨环境复制。

## 配置后怎样才算成功

依次确认：工具路径能执行 → 简单程序能编译运行 → 输入正确 → 调试器能停到断点 → 额外库例子能运行。某一个勾通过不能替代其他步骤。

Linux编译、输入、多文件链接和命令行GDB已通过开发链路检查；VS Code F5界面尚未自动操作。STM32接线、烧录与实际LED现象必须有开发板才能验证，不能把电脑上存在工具当作硬件已通。

[日常使用手册](../环境使用手册.md) · [C++学习入口](../../cpp/学习入口.md)
