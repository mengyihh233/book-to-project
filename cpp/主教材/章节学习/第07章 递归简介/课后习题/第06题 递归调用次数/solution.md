# 第7章 · 习题6：递归调用次数 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 计数器要在函数**入口**加一，终止分支也算一次调用。
- fib(0) 的调用次数是 1，不是 0。
- 调用次数大约 2·fib(n+1)-1，可以拿它自查：n=10 时应为 177。

## 容易错的边界

- n 超过 24 会慢到超时（指数级），题目把上限定在 24。
- 计数器用 long long，别用 int 赌。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long calls = 0;

long long fibCounted(int n) {
    /* BEGIN 1 */
        ++calls;
    if (n < 2) return n;
    return fibCounted(n - 1) + fibCounted(n - 2);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 24) {
            throw std::invalid_argument("n 必须在 0 到 24 之间");
        }
        /* BEGIN 2 */
                const long long value = fibCounted(n);
        std::cout << "n=" << n << " fib=" << value << " calls=" << calls << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
