# 第11章 · 习题7：数组版归并排序 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 归并的两半各自有序后，用两个下标比大小、谁小先放。
- 合并结果先写进 `buffer`，再整段搬回 `data[left..right]`，否则会覆盖未处理的数据。
- `n=1` 与空区间都要能直接返回，递归才会停。

## 容易错的边界

- 数组下标用 `int` 够（10 万），但合并时的临时容量别开小了。
- 同样的值要保持原顺序（稳定），比较写 `<=` 才能稳定。
- 别直接调 `std::sort`——这题练的是归并。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

void mergeSort(int* data, int left, int right, int* buffer) {
    /* BEGIN 1 */
        if (left >= right) return;
    const int mid = left + (right - left) / 2;
    mergeSort(data, left, mid, buffer);
    mergeSort(data, mid + 1, right, buffer);
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) buffer[k++] = data[i++];
        else buffer[k++] = data[j++];
    }
    while (i <= mid) buffer[k++] = data[i++];
    while (j <= right) buffer[k++] = data[j++];
    for (int t = left; t <= right; ++t) data[t] = buffer[t];
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100000) {
            throw std::invalid_argument("n 必须在 1 到 100000 之间");
        }
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> data[i])) throw std::invalid_argument("数字个数不足");
        }
        /* BEGIN 2 */
                std::vector<int> buffer(n);
        mergeSort(data.data(), 0, n - 1, buffer.data());
        for (int i = 0; i < n; ++i) {
            if (i) std::cout << ' ';
            std::cout << data[i];
        }
        std::cout << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
