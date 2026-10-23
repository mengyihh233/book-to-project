# 第7章 · 习题5：迭代版斐波那契 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- fib(0)=0、fib(1)=1 是基本情况，循环从 2 开始。
- fib(90)=2880067194370816120，`int` 早就溢出了，用 long long。
- 迭代写法只保留前两项，不要开数组。

## 容易错的边界

- n=90 时恰好卡在 long long 上限内，n=91 就会溢出——所以题目把上限定在 90。
- 别把 fib(0) 写成 1。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long fib(int n) {
    /* BEGIN 1 */
        if (n < 2) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        const long long c = a + b;
        a = b;
        b = c;
    }
    return b;
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 90) {
            throw std::invalid_argument("n 必须在 0 到 90 之间");
        }
        /* BEGIN 2 */
                std::cout << fib(n) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
