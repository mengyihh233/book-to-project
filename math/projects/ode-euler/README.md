# C++选做：欧拉法与精确解

对y′=ky、y(0)=y0，用N步欧拉法估计y(T)，与y0·exp(kT)比较。输入N T y0 k；1≤N≤10000，0≤T≤20，|y0|≤100，|k|≤5。不要把数值近似当作解析解。

先在notes.md写预期，work.cpp是自己的独立实现，reference.cpp仅供对照。浮点输出用空格分隔的key=value，名称与参考一致；错误输入退出2，stdout为空。参考检查通过不等于自己完成。

Windows在仓库根目录运行：

```powershell
python tools/study.py run math/projects/ode-euler/reference.cpp --input math/projects/ode-euler/input.txt
python tools/check-math.py --project ode-euler --work
```

WSL在仓库根目录运行同一份文件：

```bash
python3 tools/wsl-study.py run math/projects/ode-euler/reference.cpp --input math/projects/ode-euler/input.txt
python3 tools/check-math.py --project ode-euler --work
```

第一次观察可跑reference.cpp；作答时改为work.cpp。OpenCV仅opencv项目需要，其余仅C++标准库；不为数学阅读安装额外插件或运行环境。[环境说明](../../环境与编程说明.md) · [原书定位](../../../books/calculus-stewart.pdf#page=644)
