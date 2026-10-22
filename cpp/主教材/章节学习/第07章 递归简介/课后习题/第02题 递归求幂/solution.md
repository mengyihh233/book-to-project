# 第7章 · 习题2：递归求幂 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 0 次方是 1（包括 0⁰ 也按 1 处理，题目规定了）。
- 负底数的奇数次幂是负数，别丢符号。
- 用 long long：10¹⁸ 刚好放得下。

## 容易错的边界

- 指数为负不是这道题的范围，要报错。
- 递归终止条件写成 exp==0，别写 exp==1 漏掉 0 次方。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long power(long long base, int exp) {
    /* BEGIN 1 */
        if (exp == 0) return 1;
    return base * power(base, exp - 1);
    /* END 1 */
}

int main() {
    try {
        long long base = 0;
        int exp = 0;
        if (!(std::cin >> base >> exp) || base < -10 || base > 10 || exp < 0 || exp > 18) {
            throw std::invalid_argument("底数要在 -10..10，指数要在 0..18");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                std::cout << power(base, exp) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
