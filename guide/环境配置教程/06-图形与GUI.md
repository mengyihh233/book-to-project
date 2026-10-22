# 图形学、OpenGL、SVG和GUI不是同一种环境

| 本区内容 | 实际需要 | 入口 |
|---|---|---|
| graphics的C算法练习 | 普通gcc、C11、数学库 | 图形学C工作区 |
| Roberts第2章16—18 | C++生成SVG，浏览器查看 | 原书对应题目录 |
| OpenGL三角形/相机项目 | Windows图形驱动、GLFW、GLEW、OpenGL、GLM头文件 | OpenGL工作区 |
| PPP的Graph_lib/GUI示例 | 兼容参考库、FLTK及匹配运行库 | cpp/gui及PPP参考区 |

SVG是图形文件，普通终端打印SVG文本不会自动变成窗口。渲染任务保存output/work.svg后，用浏览器打开；这不要求安装Stanford旧图形窗口库。

## OpenGL的分工

GLFW建立窗口和上下文；GLEW用于本区加载OpenGL入口；GLM提供数学头文件。它们不是显卡驱动，装了头文件也不保证GPU支持程序要求的上下文。

当前Windows工具链接-lglfw3 -lglew32 -lopengl32 -lgdi32；不把其他教程的GLAD方案与本区GLEW方案直接拼在同一工程。先运行first-triangle，再修改颜色/坐标；相机项目用tools/run-camera.py。

普通启动会出现图形窗口，Esc关闭。数学检查与隐藏GPU验收是不同检查；不要把数学断言通过当作画面已经出现。已有图像证据是此前实际渲染结果，新机器需要重新验证驱动与上下文。

## FLTK与原书接口

FLTK隔离在仓库根目录/vendor/fltk/ucrt64，Graph_lib兼容文件在vendor/ppp2-adapted。tools/study.py识别Simple_window.h/Graph.h/GUI.h时会链接相应实现；不要只把一个头文件拷到新目录就认为依赖已齐。

Roberts的旧Stanford接口、PPP的Graph_lib、OpenGL三者不能混称一套库。当前Roberts入门题优先标准C++；静态图形题是明确的SVG教学适配。

Linux普通C++入口已恢复，但这不自动保证所有Windows GUI示例原样在WSL弹窗；需要Linux版本库及图形显示环境，再按实际项目配置。

参考：[GLFW构建应用说明](https://www.glfw.org/docs/latest/build_guide.html)。
