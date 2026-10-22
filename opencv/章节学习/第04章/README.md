# 第4章：Mat 共享、复制与 ROI

> **本题只改一份文件的 3 个补全区。** 不需要图片、键盘输入或图形窗口。

[打开我的作答](work/main.cpp) · [做完后看解析](solution.md)

## 1 · 题目是什么

用一个 4 行 5 列的灰度小矩阵，观察“两个 Mat 对象是否在改同一块像素”。把共享与 `clone()`、ROI 与行步长、按值传参放在同一次实验中比较。

这是第4章中文自编配套 **CV-L04**，不是原书同号题的答案。[原书正文](../../../reader/opencv/OEBPS/ch04.html#images_and_large_array_types) · [原书章末习题](../../../reader/opencv/OEBPS/ch04.html#exercises-id00008)

## 2 · 实现什么

主程序已经给好建图、取 ROI、修改、调用与输出。你完成下面 3 处，先预测再运行：

| 补全区 | 写什么 | 要理解什么 |
|---|---|---|
| 1 · 共享与独立复制 | 给 `shared`、`independent` 赋值 | 普通赋值共享像素，`clone()` 复制像素 |
| 2 · `sumPixels` | 逐行累加矩阵的全部有效像素，返回整数和 | ROI 每行有效宽度可能小于行步长 |
| 3 · `paintSharedPixels` | 将参数矩阵的像素统一设为 9 | Mat 按值传参仍可能共享像素 |

限定 `sumPixels` 接收二维 `CV_8UC1` 矩阵：**使用 `ptr<uchar>(row)` 逐行取指针，再按列遍历**。这里只练一种像素类型，不把它泛化为所有图像。

## 3 · 写在哪里

只在[我的作答/main.cpp](work/main.cpp) 的 `/* BEGIN N ... */` 与 `/* END N */` 之间写。

- 删除该区的占位 `throw`，替换成自己的实现。
- `main()` 已给好；两个函数的声明在前，定义在后。不要再写第二个 `main()`，也不要把函数定义放进 `main()`。
- 可先做补全区 1，再做 2、3。剩余的占位提示会指出还没完成哪一处。

这里的“我的作答”是中文目录入口，实际指向本章的 `work` 文件夹，两处是同一份文件。

## 4 · 怎么做

### 先看懂对象与数据

```text
source ──┐
         ├── 同一块像素数据（shared、ROI 的修改会被 source 看见）
shared ──┘

independent ── clone 复制得到的另一块像素
```

`cv::Mat` 保存尺寸、类型、数据位置等信息。复制 Mat 对象不一定复制像素；这与 `int` 复制值的直觉不同。

### 顺着主程序观察

1. **共享与复制：** 在修改 `source(0,0)` 前完成两种复制。之后把源值改为 99，预测两个对象各读到什么。
2. **ROI 与逐行遍历：** 已给定 `Rect(1,1,3,2)`，将这块区域设为 7。`Rect` 的顺序是 **x、y、宽、高**；`at` 的顺序是 **行、列**。因此 ROI 的 `(0,0)` 对应原图 `(1,1)`，原图 `(1,4)` 在 ROI 外。
3. **按值传参：** 完成 `paintSharedPixels(cv::Mat image)` 后，观察调用者的像素。再对独立副本修改，判断原图是否还会跟着变。

本例 ROI 有 2 行，每行 3 个有效字节，但相邻行起点间隔 5 字节。不能从 `roi.data` 开始直接遍历 `rows * cols` 个字节来求和。`ptr<uchar>(row)` 会定位到指定行，再只读该行的 3 列。

提示接口：`cv::Mat` 赋值、`.clone()`、`.setTo(...)`、`.rows`、`.cols`、`.ptr<uchar>(row)`。本例窄 ROI 不连续，`clone()` 后的新矩阵连续；不能据此断言所有 ROI 都不连续。接口说明见 [OpenCV 官方 Mat 文档](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html)。

## 5 · 输入与输出

**没有输入。** 直接运行即可；本题不用 `input.txt`，也不用“本题：用样例输入运行”。输出语句已经给定，不要靠硬编码结果代替像素操作。

补全正确时，当前作答框架输出：

```text
share_clone=99 0
roi_map=7 0
roi_layout=5 3 0 1
roi_sum=42
roi_clone=55 7
value_parameter=9 3
```

| 输出标签 | 依次表示什么 |
|---|---|
| `share_clone` | 修改源图后，共享对象的值、提前 clone 的独立对象的值 |
| `roi_map` | ROI 内对应的原图像素、ROI 外的原图像素 |
| `roi_layout` | ROI 行步长（字节）、每行有效字节数、ROI 是否连续、clone 是否连续；0 否，1 是 |
| `roi_sum` | ROI 有效像素之和：2 × 3 × 7 = 42 |
| `roi_clone` | 修改后的 ROI 独立副本、原 ROI 的对应像素 |
| `value_parameter` | 按值传参后原矩阵的值、后来改为 3 的独立副本的值 |

未补全时，框架会输出“补全区 N 尚未完成”并结束；这是占位提醒，不是编译失败。

## 6 · 怎么运行与核验

1. 在 VS Code 打开本题的[作答文件](work/main.cpp)，保存。
2. **运行：** Ctrl+Shift+B，或“任务：运行任务” → **本题：运行作答**。逐行对照上表。
3. **检查：** “任务：运行任务” → **本题：检查作答**。本题是**人工核验**；检查入口会显示这一事实，没有独立自动评分器，不会据编译成功判定完成。

网页可以看本题代码并调用已有运行、检查入口；**编辑仍在 VS Code**。保存后刷新代码预览，确认网页和本地显示的是同一份作答。

也可在学习区根目录的 PowerShell 运行：

```powershell
& 'C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe' tools/run-current.py 'opencv/chapters/ch04/work/main.cpp'
```

WSL 使用相同文件与入口：

```bash
cd 仓库根目录
python3 tools/run-current.py opencv/chapters/ch04/work/main.cpp
```

## 7 · 做完的标准

- 6 行观察结果一致，且每个数值能用共享关系或坐标解释。
- 在同一文件中，仅把 `roiValue` 从 7 改为 3 再运行：`roi_map=3 0`、`roi_sum=18`、`roi_clone=55 3`，其余行不变。然后自行决定保留或恢复。这样能核对实现是否读取了真实像素。
- 能回答：为什么 `sumPixels(const cv::Mat& image)` 用只读引用，而 `paintSharedPixels(cv::Mat image)` 故意按值接收，仍能改到调用者的像素？

核验完再看[参考解析与 3 个补全区答案](solution.md)。[reference.cpp](reference.cpp) 是较早的完整参考实验；它的断言只核对参考实现，不证明你的文件已完成。下一步可把布局知识用于[零件检测失败场景实验](../../projects/parts-inspector/失败场景实验.md)。
