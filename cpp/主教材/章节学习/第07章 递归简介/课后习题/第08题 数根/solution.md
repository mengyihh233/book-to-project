# 第7章 · 习题8：数根 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 终止条件是一位数：x < 10 直接返回。
- 先求一次数位和，再对数位和递归——不要一次加到底只用循环。
- 数学上答案等于 `1 + (x-1) % 9`（x>0），可以拿它验算。

## 容易错的边界

- 0 的数根是 0，不是 9。
- 10¹⁸ 超过 int，读入用 long long。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

int digitalRoot(long long x) {
    /* BEGIN 1 */
        if (x < 10) return static_cast<int>(x);
    long long sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return digitalRoot(sum);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("个数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
                for (int i = 0; i < n; ++i) {
            long long v = 0;
            if (!(std::cin >> v) || v < 0) throw std::invalid_argument("每行一个非负整数");
            std::cout << digitalRoot(v) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
