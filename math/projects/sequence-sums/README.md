# C++选做：数列与级数的区别

输入项数N，0≤N≤100000。分别求n从0到N−1的(1/3)^n之和，以及n从1到N的1/[n(n+1)]之和。N=0表示空和0。不要把通项极限与部分和极限混为一谈。

先在notes.md写预期，work.cpp是自己的独立实现，reference.cpp仅供对照。浮点输出用空格分隔的key=value，名称与参考一致；错误输入退出2，stdout为空。参考检查通过不等于自己完成。

Windows在仓库根目录运行：

```powershell
python tools/study.py run math/projects/sequence-sums/reference.cpp --input math/projects/sequence-sums/input.txt
python tools/check-math.py --project sequence-sums --work
```

WSL在仓库根目录运行同一份文件：

```bash
python3 tools/wsl-study.py run math/projects/sequence-sums/reference.cpp --input math/projects/sequence-sums/input.txt
python3 tools/check-math.py --project sequence-sums --work
```

第一次观察可跑reference.cpp；作答时改为work.cpp。OpenCV仅opencv项目需要，其余仅C++标准库；不为数学阅读安装额外插件或运行环境。[环境说明](../../环境与编程说明.md) · [原书定位](../../../books/calculus-stewart.pdf#page=810)
