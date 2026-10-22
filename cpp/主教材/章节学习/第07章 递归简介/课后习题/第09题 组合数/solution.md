# 第7章 · 习题9：组合数 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 两个终止条件缺一不可：k==0 和 k==n 都返回 1。
- 帕斯卡恒等式 `C(n,k)=C(n-1,k-1)+C(n-1,k)`，比按阶乘算更稳。
- C(30,15)=155117520，放得进 int，但用 long long 更保险。

## 容易错的边界

- 只写 k==0 会在 k==n 时多递归一层，虽然结果对但很慢。
- k > n 不能返回 0，要判非法。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>

long long comb(int n, int k) {
    /* BEGIN 1 */
        if (k == 0 || k == n) return 1;
    return comb(n - 1, k - 1) + comb(n - 1, k);
    /* END 1 */
}

int main() {
    try {
        int m = 0;
        if (!(std::cin >> m) || m < 1 || m > 50) {
            throw std::invalid_argument("组数必须在 1 到 50 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                for (int i = 0; i < m; ++i) {
            int n = 0, k = 0;
            if (!(std::cin >> n >> k)) throw std::invalid_argument("每行两个整数");
            if (n < 0 || k < 0 || k > n || n > 30) throw std::invalid_argument("要求 0 <= k <= n <= 30");
            std::cout << comb(n, k) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
