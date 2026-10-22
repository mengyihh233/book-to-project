# OpenCV：编译、链接、运行三层配置

本区使用C++ OpenCV。Python的pip install opencv-python不会自动配置C++头文件与链接库。

## Windows现有配置

| 层次 | 本机配置 |
|---|---|
| 头文件 | D:/c++/MYSYS2/ucrt64/include/opencv4 |
| 链接库 | D:/c++/MYSYS2/ucrt64/lib，使用UCRT64 GCC对应库 |
| 运行依赖 | UCRT64/bin及vendor/opencv-deps/ucrt64/bin，由工具按程序配置 |
| 编辑器提示 | opencv/.vscode/settings.json中的compilerPath、includePath |

tools/study.py对opencv目录下的源码加入实际-I、-L及所需-lopencv_*。这与提示用includePath是两套职责。本机使用MinGW库，不能直接拿另一个MSVC构建包混着链接。

## 第一次跑通

打开workspaces/opencv.code-workspace，从Mat/灰度/ROI学起。已有零件计数项目可运行：

```powershell
$learningPython = 'C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe'
Set-Location '仓库根目录'
& $learningPython tools/inspect-parts.py --demo
```

--demo按需生成合成图，每次写新输出目录。查看overlay.png、mask.png、report.json。使用自己的图片时改--input；批处理用--batch，不把输出放进输入目录。

## Linux环境的范围

Ubuntu已保留OpenCV core/imgproc/imgcodecs开发库，能支持部分基础图像处理。它不是Windows全部模块的镜像；需要HighGUI窗口、相机、特征点或ML的程序，要先确认对应开发库是否存在。

Linux头文件通常通过pkg-config或CMake查找，链接.so；Windows本机这里用已有MinGW配置。若将来扩建Linux OpenCV环境，按[OpenCV官方安装指南](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)针对需要的模块处理，不要先复制Windows DLL过去。

## 先按阶段排错

头文件缺失→看-I和包是否有开发头；undefined reference→看模块库和工具链；DLL缺失→看运行环境；读图失败→看路径、格式和解码结果。改参数只能解决算法问题，不能修复链接器配置。

本轮不重复安装OpenCV，也不宣称工业相机SDK、GPU计算和深度学习训练环境已具备。
