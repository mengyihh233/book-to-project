# 第7章 · 习题7：数位之和 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 终止条件是「一位数」：x < 10 时直接返回 x。
- 每次剥掉最低位：`x % 10` 加上 `digitSum(x / 10)`。
- 10¹⁸ 超过 int，读入要用 long long。

## 容易错的边界

- 0 的数位和是 0，不是非法输入。
- 用无符号类型会把负数读成大正数，乖乖用 long long。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long digitSum(long long x) {
    /* BEGIN 1 */
        if (x < 10) return x;
    return x % 10 + digitSum(x / 10);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("个数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                for (int i = 0; i < n; ++i) {
            long long v = 0;
            if (!(std::cin >> v) || v < 0) throw std::invalid_argument("每行一个非负整数");
            std::cout << digitSum(v) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
