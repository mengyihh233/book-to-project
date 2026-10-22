# CV-L04 参考解析：追踪共享的像素

[回题目](README.md) · [回我的作答](work/main.cpp)

先在自己的文件里预测并尝试，再对照下面 3 处。它们对应同一份作答文件，不要另建答案工程，也不要覆盖自己的完整文件。

## 补全区 1：复制对象头，还是复制像素

```cpp
shared = source;
independent = source.clone();
```

`shared` 与 `source` 访问同一块像素。`independent` 在源图还全为 0 时复制了像素；后来源图 `(0,0)` 改成 99，前者看到 99，后者仍看到 0。因此 `share_clone=99 0`。

如果两个都写成普通赋值，会观察到 `99 99`；如果两个都 clone，则是 `0 0`。这两个错法也能编译，说明编译成功不足以完成本题。

## 补全区 2：正确跨过行间隔

```cpp
int sum = 0;
for (int row = 0; row < image.rows; ++row) {
    const uchar* pixels = image.ptr<uchar>(row);
    for (int col = 0; col < image.cols; ++col) {
        sum += pixels[col];
    }
}
return sum;
```

本例 ROI 每行有效 3 字节，相邻行起点间隔 5 字节。`ptr` 按真实行步长定位到一行；内层只读取该行的 3 个有效像素，所以总和是 2 × 3 × 7 = 42。

`roi_layout=5 3 0 1` 依次说明：行步长 5 字节、有效行宽 3 字节、原 ROI 不连续、clone 的矩阵连续。不要将行步长直接当成列数，字节数与元素数只有在本例单通道 `uchar` 下恰好相同。

这里参数用 `const cv::Mat&` 表明本函数只读取矩阵。`const` 访问约束与“像素是否独立复制”是不同问题。

## 补全区 3：按值传 Mat 仍可能共享像素

```cpp
image.setTo(9);
```

调用时复制了 Mat 参数对象，但两个对象继续访问同一块像素；因此传入 `input` 后，调用者读到 9。随后 `safeInput = input.clone()` 才建立独立像素，修改副本为 3 不改变 `input`，输出 `value_parameter=9 3`。

这里练的是“在共享数据上修改像素”。如果在函数里将局部参数**重新赋值为另一个 Mat**，那是在更换局部对象的指向，不能把两种操作混为一谈。也不要推导成所有 C++ 类按值复制都有同样行为。

## 按行核对本题

当前作答框架在 3 处正确补全后输出：

```text
share_clone=99 0
roi_map=7 0
roi_layout=5 3 0 1
roi_sum=42
roi_clone=55 7
value_parameter=9 3
```

ROI `(行0,列0)` 对应原图 `(行1,列1)`；`Rect` 的 x 对应列、y 对应行。`roi.setTo(7)` 改到原图的窗口内，所以 `roi_map` 前一个值为 7；窗口外 `(1,4)` 仍是 0。之后修改 `packed` 的独立像素为 55，原 ROI 仍是 7。

### 用一次变更检验理解

只将主程序的 `roiValue` 从 7 改为 3，重新运行。应变成：

```text
roi_map=3 0
roi_sum=18
roi_clone=55 3
```

其他行不变。若 `roi_sum` 仍为 42，应检查是否把预期结果直接写死，或没有读取实际矩阵。完成后可把常量恢复为 7。

## 这次核验能说明什么

本题保持**人工核验**，没有独立自动评分。上述固定小矩阵帮助观察共享与布局；输出相同仍需解释实现，不代表已覆盖所有矩阵类型和尺寸。不要做越界访问，也不要把本例的 `uchar` 指针写法直接用于彩色或浮点图像。

[reference.cpp](reference.cpp) 是较早的完整实验，它比当前作答少一行 `roi_layout`、多一句断言后的提示。其断言核验的是参考实现；参考程序运行成功不能作为自己的完成证明。接口行为可查 [OpenCV 官方 Mat 文档](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html)。
