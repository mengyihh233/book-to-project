# 第10章 · 习题5：线性查找与二分查找的比较次数 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 「比较次数」数的是**元素之间比了几次**，不是循环转了几圈——二分里每轮恰好一次比较。
- 线性查找没找到时也是 n 次：`for` 循环里先 `++count` 再判断，顺序反了会少算一次。
- 二分用 `low + (high - low) / 2` 取下中点，和题目给的定义一致；换成上中点结果会不同。
- 这正是本章要看的差别：线性是 O(N)，二分是 O(log N)——9 个数看不出，n = 1000 时差 100 倍。

## 容易错的边界

- 二分循环条件写成 `low < high` 会漏掉最后一个元素，比较次数也会少一次。
- 找到之后别忘了把这次比较算进去——`++count` 要在比较之前。
- `mid` 用 `(low + high) / 2` 在极端情况下会溢出，虽然这题 n ≤ 1000 不会，但习惯要改过来。
- 数组里允许重复值，线性查找停在**第一个**相等的位置，二分停在**中间命中**的那一个，两者次数不同是正常的。

## 参考实现

```cpp
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int linearComparisons(const std::vector<long long>& values, long long key);

int binaryComparisons(const std::vector<long long>& values, long long key);

// 从下标 0 开始逐个比较，返回比较次数（找不到就是 n 次）。
int linearComparisons(const std::vector<long long>& values, long long key) {
    /* BEGIN 1 */
    int count = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        ++count;
        if (values[i] == key) return count;
    }
    return count;
    /* END 1 */
}

// 折半查找，返回比较次数。
int binaryComparisons(const std::vector<long long>& values, long long key) {
    /* BEGIN 2 */
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;
    int count = 0;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        ++count;
        if (values[static_cast<std::size_t>(mid)] == key) return count;
        if (values[static_cast<std::size_t>(mid)] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return count;
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("元素个数必须在 1 到 1000 之间");
        }

        std::vector<long long> values(static_cast<std::size_t>(n));
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> values[static_cast<std::size_t>(i)])) {
                throw std::invalid_argument("数字个数不足");
            }
            if (i > 0 && values[static_cast<std::size_t>(i)] < values[static_cast<std::size_t>(i - 1)]) {
                throw std::invalid_argument("数组必须升序排列");
            }
        }

        int q = 0;
        if (!(std::cin >> q) || q < 0 || q > 1000) {
            throw std::invalid_argument("查询个数必须在 0 到 1000 之间");
        }

        std::vector<long long> queries(static_cast<std::size_t>(q));
        for (int i = 0; i < q; ++i) {
            if (!(std::cin >> queries[static_cast<std::size_t>(i)])) {
                throw std::invalid_argument("查询值个数不足");
            }
        }

        for (long long key : queries) {
            std::cout << key << " 线性=" << linearComparisons(values, key)
                      << " 二分=" << binaryComparisons(values, key) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
```
