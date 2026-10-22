# 第7章 · 习题4：最大公约数 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 欧几里得算法：`gcd(x,y) = gcd(y, x%y)`，终止条件 `y==0`。
- `gcd(0, 5)` 应该是 5，`gcd(0,0)` 规定为 0——终止条件正好覆盖。
- x、y 到 10⁹ 时用 long long 更稳。

## 容易错的边界

- 别用 `%` 之外的方法硬枚举，10⁹ 会超时。
- 负数不是本题范围，直接报错。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long gcd(long long x, long long y) {
    /* BEGIN 1 */
        if (y == 0) return x;
    return gcd(y, x % y);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("组数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                for (int i = 0; i < n; ++i) {
            long long x = 0, y = 0;
            if (!(std::cin >> x >> y) || x < 0 || y < 0) throw std::invalid_argument("每行两个非负整数");
            std::cout << gcd(x, y) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
