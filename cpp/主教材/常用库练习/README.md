# 常用库练习：按用途分开，相近函数放一起


> **这一页怎么用**（一页多题，不是一次做完）
>
> - **是什么**：8 组常用库练习，按用途分开，不是 8 道必做题。
> - **每次只做一组**：看下面的表，选当前章节对应的那一组，10—25 分钟；已经熟的可以直接跳过。
> - **写在哪**：每组写在自己那一行的「你的文件」里，一组一个 cpp，不要合并。
> - **怎么验**：这页**没有自动判分**。先写下预测，再运行，最后对照参考实现找差异，记录一处边界。
> - **什么算做完**：能预测这一组的输出并解释差异，不是跑通就算。

[文件和目录怎么用](../../README.md)：先README，再自己的work，最后解析；自动检查文件由任务读取。

每组一份作答源码，一份参考源码；题目与解析集中在这里，不为每个函数建题，也不把所有库塞进一个作答文件。**每次只选当前章节的一组，10—25分钟**，已有熟悉用法可跳过。标准库接口与Stanford教材库分开说明。

| 组 | 库/用途 | 章节 | 你的文件 | 参考（做后再看） |
|---|---|---|---|---|
| 数学库 | cmath | 2 | [我的作答/math.cpp](我的作答/math.cpp) | [参考实现/math.cpp](参考实现/math.cpp) |
| 字符处理 | cctype | 3 | [我的作答/characters.cpp](我的作答/characters.cpp) | [参考实现/characters.cpp](参考实现/characters.cpp) |
| 字符串 | string / cstring | 3 | [我的作答/strings.cpp](我的作答/strings.cpp) | [参考实现/strings.cpp](参考实现/strings.cpp) |
| 教材 strlib 适配 | 数字/文本转换、ASCII大写 | 3 | [我的作答/stanford-strings.cpp](我的作答/stanford-strings.cpp) · [题目](stanford-strings.md) | [参考实现/stanford-strings.cpp](参考实现/stanford-strings.cpp) |
| 流与格式 | iostream / sstream / iomanip | 4 | [我的作答/streams.cpp](我的作答/streams.cpp) | [参考实现/streams.cpp](参考实现/streams.cpp) |
| 容器常用接口 | vector / stack / queue / map / set | 5 | [我的作答/containers.cpp](我的作答/containers.cpp) | [参考实现/containers.cpp](参考实现/containers.cpp) |
| STL算法与回调 | algorithm / numeric | 20 | [我的作答/algorithms.cpp](我的作答/algorithms.cpp) | [参考实现/algorithms.cpp](参考实现/algorithms.cpp) |
| 类与所有权 | memory / utility（类概念补充） | 6、12 | [我的作答/objects.cpp](我的作答/objects.cpp) | [参考实现/objects.cpp](参考实现/objects.cpp) |

原来的我的作答/main.cpp保留你的历史作答；今后按上表选文件，不要求把旧内容再抄一遍。reference.cpp只是汇总运行这些参考文件，没有另一套重复实现。各参考文件均可单独编译。

## 与章内主练习怎么分工

这里练“调用库、看返回值、处理失败”，章内主练习练“独立实现与组织程序”。例如先在containers.cpp观察stack接口，再回第5章做括号匹配；不要把相同API演示复制到每个章节。第15、17章需要复习map/set时仍用这一组，后续只另练内部实现与算法差别。

## 数学库：math.cpp

**任务**：调用表2-1中的13项；重点比较负数的floor/ceil、弧度与atan2(y,x)。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 字符处理：characters.cpp

**任务**：把A、a、7、F、!、空格、换行放进同一分类表，再转换大小写；比较非0而不是==1。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 字符串：strings.cpp

**任务**：沿用文件名image_007.png，完成查找、截取、增删替换；最后比较string长度和C字符串长度。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 流与格式：streams.cpp

**任务**：同一文件里练格式状态、词/行/字符读取、严格整数转换、失败恢复；不用创建临时数据文件。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 容器常用接口：containers.cpp

**任务**：用同一批小数据观察顺序容器、栈队列及映射集合；这里只调用接口，不再重复实现括号匹配/词频项目。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## STL算法与回调：algorithms.cpp

**任务**：把排序、去重、查找、平方、筛选串成一条数据流水线；同一个谓词分别用于vector与list。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 类与所有权：objects.cpp

**任务**：用二维Point练构造、const查询、operator+返回值；用unique_ptr观察move前后谁拥有对象。

先在本组work写出输入、调用和预测，跑完再记录一处边界；解析见[统一核对](solution.md)。

## 本轮补齐的用法

- 字符串组：补c_str、strlen、strcmp与嵌入零字符区别；观察指针有效期，不向c_str返回的const指针写入，不使用已失效指针。
- 流组：在原格式基础上补showpoint/noshowpoint、uppercase/nouppercase、endl/flush，并练clear/ignore恢复。原书表4-1所列操纵符已都有调用；defaultfloat/flush等作为相关补充。endl的刷新不能仅凭内存流的字符串内容证明性能效果。
- 容器组：集中练vector的size/capacity/reserve/resize/at/front/back/push_back/pop_back/insert/erase/clear；stack与queue的push/pop/top/front/back；map的[]/find/erase；set的insert/count/erase。空容器先判断，不故意执行未定义行为。
- 算法组：sort、unique、find、count、binary_search、lower_bound、upper_bound、accumulate、transform、remove_if和lambda谓词；有序查找先满足排序前提。unique只合并相邻重复值，本组先排序以达到全局去重。
- 类与所有权组：第6章Point与operator+，第12章const、返回值与资源转交；这是重点补充，不代替原书完整有理数、token扫描器或CharStack实现。

## 教材位置与边界

[PDF55数学库表](../../../books/cpp-roberts.pdf#page=55) · [PDF108字符库表](../../../books/cpp-roberts.pdf#page=108) · [PDF109字符串修改](../../../books/cpp-roberts.pdf#page=109) · [PDF124—125格式表](../../../books/cpp-roberts.pdf#page=124)。容器组使用**标准库**，是对原书第5章的调用适配；不是逐一运行Stanford Vector/Grid/Map等原始API。算法与lambda是第20章相关补充，不宣称与原书每个版本完全一致。

PDF114页strlib的五个接口名称已有一组 [roberts_compat 教学适配调用练习](stanford-strings.md)，共享头提供函数，学生只练调用与边界。自编适配已验证；Stanford原库的直接调用、error机制和其他接口仍需单独验收，不标作原库全覆盖。原书历史库保留，不要求为当前这些标准库练习安装图形后端。

## 运行方式

VS Code打开上表相应work源码，用现有“当前文件”编译运行。Windows在D:\Book-Learning根目录，例如：

```powershell
python tools/study.py run cpp/主教材/常用库练习/我的作答/containers.cpp
```

WSL在仓库根目录根目录：

```bash
python3 tools/wsl-study.py run cpp/主教材/常用库练习/我的作答/containers.cpp
```

将containers换成正在学的组名。核对参考时仅把“我的作答”改为“参考实现”。需要维护全部参考时运行 cpp/主教材/常用库练习/reference.cpp 汇总入口。作答文件初始明确提示未实现；本组没有原书题号自动评分，不用practice.py检查它。参考通过不改变个人进度。

## 选做连接：值传递不等于数据一定独立

当你进入机器视觉，cv::Mat按值复制对象头时仍可能共享像素；不能机械套用int参数的直觉。先做[Mat共享、clone、ROI与步长](../../../opencv/chapters/ch04/README.md)，画清对象与底层数据，再回本组解释自己的类型实际复制了什么。它复用OpenCV第4章文件，不另建C++练习工程。

<!-- study-check:start -->
## 运行与检查

1. 打开本题自己的作答文件，保存修改。
2. **运行：** Ctrl+Shift+B，或“任务：运行任务” → **本题：运行作答**。这一步不判题。
3. **核对：** “任务：运行任务” → **本题：检查作答**。本题没有独立自动评分。检查入口会明确提示人工自检，不把参考实现通过或编译成功当作你的作答通过。

input.txt是手动测试输入；检查数据不是填答案的位置。无需自己挑选判分脚本，“本题：检查作答”会读取本题规则。
<!-- study-check:end -->
