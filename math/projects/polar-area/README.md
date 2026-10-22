# C++选做：极坐标面积与重复描绘

输入类型、幅度a、分段数N。类型circle、cardioid、rose3分别为r=a、a(1+cosθ)、a sin3θ。0≤a≤100，1≤N≤1000000。用中点法估计(1/2)∫r²dθ；rose3只积0到π，其他积0到2π。

先在notes.md写预期，work.cpp是自己的独立实现，reference.cpp仅供对照。浮点输出用空格分隔的key=value，名称与参考一致；错误输入退出2，stdout为空。参考检查通过不等于自己完成。

Windows在仓库根目录运行：

```powershell
python tools/study.py run math/projects/polar-area/reference.cpp --input math/projects/polar-area/input.txt
python tools/check-math.py --project polar-area --work
```

WSL在仓库根目录运行同一份文件：

```bash
python3 tools/wsl-study.py run math/projects/polar-area/reference.cpp --input math/projects/polar-area/input.txt
python3 tools/check-math.py --project polar-area --work
```

第一次观察可跑reference.cpp；作答时改为work.cpp。OpenCV仅opencv项目需要，其余仅C++标准库；不为数学阅读安装额外插件或运行环境。[环境说明](../../环境与编程说明.md) · [原书定位](../../../books/calculus-stewart.pdf#page=726)
