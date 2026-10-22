# VS Code配置：每个文件只管一部分

## 先确认打开了哪个窗口

Windows本地窗口使用本机工具；WSL窗口左下角显示WSL: Ubuntu，工具与多数工作区扩展运行在Ubuntu。窗口里新开Ubuntu终端，不会自动把整个窗口的任务和调试器切成Linux。

文件夹工作区是打开一个目录；.code-workspace可以包含多个根目录。本学习区的Windows C++和WSL工作区均为多根工作区。每个根目录的.vscode可能影响该根目录，不能假定任意父目录的.vscode都会被继承。

## 配置文件关系

| 文件/区域 | 职责 | 典型字段 |
|---|---|---|
| settings.json / workspace的settings | 编辑和环境偏好 | compilerPath、cppStandard、终端默认配置 |
| tasks.json / workspace的tasks | 执行外部命令 | command、args、problemMatcher、label |
| launch.json / workspace的launch | 如何启动调试 | program、miDebuggerPath、preLaunchTask |
| c_cpp_properties.json | C/C++提示与解析配置的一种方式 | compilerPath、includePath、intelliSenseMode |
| extensions.recommendations | 推荐哪些扩展 | 不是“只允许这些扩展” |

本学习区主要用settings里的C_Cpp.default.*，不要求每题再创建一份c_cpp_properties.json。任务通过Python调用编译器，不是让VS Code隐式猜一个编译方式。

## 四个关键字段怎样连起来

tasks的label是任务名字；launch的preLaunchTask必须对应它。编译输出在哪里，launch的program就必须指向哪里。miDebuggerPath是调试器，不是被调试程序。

当前Windows用“Windows: 编译当前文件供调试”，输出仓库根目录/build/active-program.exe；Linux用“WSL: 编译当前C++供调试”，输出~/.cache/book-learning/active-program。两者不混用。

| 常用变量 | 含义 | 注意 |
|---|---|---|
| ${file} | 当前活动文件的绝对路径 | 先选中.cpp并保存 |
| ${fileDirname} | 当前文件所在目录 | input.txt通常在这里 |
| ${workspaceFolder} | 当前上下文的工作区根目录 | 多根工作区要看归属 |
| ${env:HOME} | 当前运行上下文的HOME | 本例Linux调试使用远程HOME |

## 从界面查真实配置

Ctrl+,打开设置，查看用户/工作区标签；搜索compilerPath。Ctrl+Shift+P执行“C/C++: Log Diagnostics”查看解析器实际使用的编译器和包含目录。构建失败先读“终端”的编译命令和第一条错误，红线诊断则看“输出→C/C++”。

选任务：终端→运行任务。Ctrl+Shift+B打开构建任务选择；不要因为有多个任务就认为所有任务都要执行。F9断点、F5调试、F10逐过程、F11进入函数、Shift+F5结束。

## 插件、配置文件与WSL

“已安装”不等于“已激活”。用“Developer: Show Running Extensions”查看实际运行的扩展。WSL窗口中注意扩展装在本地还是“WSL: Ubuntu”；界面扩展可能在Windows侧，语言工具扩展在远程侧。

如果要把C++、STM32、前端插件严格分开，可在VS Code的Profiles管理中创建命名配置文件，并分别安装需要的扩展、关联工作区。它与Windows/WSL是两个维度：Profile管偏好与扩展集合，远程连接决定代码和工具运行在哪儿。本轮提供教程，不自动重建或卸载你的全局扩展。

不要为解决一个工程问题反复改用户全局设置。先确定当前窗口、配置层级、任务和工具路径；新建配置前保留可用配置。

参考：[C/C++配置字段](https://code.visualstudio.com/docs/cpp/customize-cpp-settings)、[Profiles](https://code.visualstudio.com/docs/configure/profiles)、[WSL扩展运行位置](https://code.visualstudio.com/docs/remote/wsl)。
