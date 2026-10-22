# OpenCV选做：偏导数与图像梯度

不使用摄像头或个人图片，构造I(u,v)=2u+3v的小型浮点图像。输入奇数边长N，3≤N≤101。在中心用Sobel核、scale=1/8估计偏导数。图像行v向下，因此数学坐标y向上时对应符号要翻转。

先在notes.md写预期，work.cpp是自己的独立实现，reference.cpp仅供对照。浮点输出用空格分隔的key=value，名称与参考一致；错误输入退出2，stdout为空。参考检查通过不等于自己完成。

Windows在仓库根目录运行：

```powershell
python tools/study.py run math/projects/opencv/reference.cpp --input math/projects/opencv/input.txt
python tools/check-math.py --project opencv --work
```

WSL在仓库根目录运行同一份文件：

```bash
python3 tools/wsl-study.py run math/projects/opencv/reference.cpp --input math/projects/opencv/input.txt
python3 tools/check-math.py --project opencv --work
```

第一次观察可跑reference.cpp；作答时改为work.cpp。OpenCV仅opencv项目需要，其余仅C++标准库；不为数学阅读安装额外插件或运行环境。[环境说明](../../环境与编程说明.md) · [原书定位](../../../books/calculus-stewart.pdf#page=1032)
