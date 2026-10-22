# 第7章 项目：递归基础 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：递归基础
// 第一行两个整数求最大公约数（辗转相除，递归）；第二行 n 求 n!（递归）。
#include <cstdlib>
#include <iostream>

namespace {

long long gcdOf(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);
    if (b == 0) return a;          // 基准情形：余数为 0 时，另一个数就是答案
    return gcdOf(b, a % b);
}

long long factorial(int n) {
    if (n <= 1) return 1;          // 基准情形不能漏，否则递归不收敛
    return n * factorial(n - 1);
}

}  // namespace

int main() {
    long long a = 0, b = 0;
    int n = 0;
    if (!(std::cin >> a >> b)) {
        std::cerr << "第一行需要两个整数\n";
        return 2;
    }
    if (!(std::cin >> n)) {
        std::cerr << "第二行需要一个整数\n";
        return 2;
    }
    if (a == 0 && b == 0) {
        std::cerr << "gcd(0,0) 没有定义\n";
        return 2;
    }
    if (n < 0 || n > 20) {
        std::cerr << "n 必须在 0 到 20 之间\n";
        return 2;
    }
    std::cout << "gcd " << gcdOf(a, b) << "\n";
    std::cout << "阶乘 " << factorial(n) << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `12 18` + `5` → `gcd 6` / `阶乘 120`
- [ ] `7 13` + `0` → `gcd 1` / `阶乘 1`
- [ ] `0 5` + `20` → `gcd 5` / `阶乘 2432902008176640000`
- [ ] `-4 6` + `4` → `gcd 2` / `阶乘 24`
- [ ] `0 0` + `3` → 返回 2
- [ ] `100 75` + `21` → 返回 2（n 越界）
- [ ] 阶乘用 `long long`，`20!` 不能溢出

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
