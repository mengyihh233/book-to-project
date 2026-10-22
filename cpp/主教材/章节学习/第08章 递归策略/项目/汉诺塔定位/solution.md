# 第8章 项目：汉诺塔定位 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：汉诺塔定位
// 输入 n 与 k，输出总步数 2^n-1，以及第 k 步移动的是哪个柱到哪个柱。
// 不模拟整个过程：每层递归能直接判断第 k 步落在「搬上面 n-1 个」「搬最大的」「搬回来」哪一段。
#include <iostream>
#include <string>

namespace {

void kthStep(int n, char from, char to, char via, long long k, std::string& out) {
    if (n == 0) return;
    const long long half = (1LL << (n - 1)) - 1;   // 上面 n-1 个搬完需要的步数
    if (k <= half) {
        kthStep(n - 1, from, via, to, k, out);
    } else if (k == half + 1) {
        out = std::string(1, from) + "->" + std::string(1, to);
    } else {
        kthStep(n - 1, via, to, from, k - half - 1, out);
    }
}

}  // namespace

int main() {
    int n = 0;
    long long k = 0;
    if (!(std::cin >> n >> k)) {
        std::cerr << "需要两个整数 n 和 k\n";
        return 2;
    }
    if (n < 1 || n > 16) {
        std::cerr << "n 必须在 1 到 16 之间\n";
        return 2;
    }
    const long long total = (1LL << n) - 1;
    if (k < 1 || k > total) {
        std::cerr << "k 必须在 1 到 " << total << " 之间\n";
        return 2;
    }
    std::string step;
    kthStep(n, 'A', 'C', 'B', k, step);
    std::cout << "步数 " << total << "\n";
    std::cout << "第 " << k << " 步 " << step << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `3 1` → 步数 7，第 1 步 `A->C`
- [ ] `3 4` → 第 4 步 `A->C`（中间那一搬）
- [ ] `3 7` → 第 7 步 `A->C`
- [ ] `1 1` → 步数 1，第 1 步 `A->C`
- [ ] `4 15` → 步数 15，最后一步 `B->C`
- [ ] `0 1` → 返回 2
- [ ] `17 1` → 返回 2
- [ ] `3 8` → 返回 2（k 超过 7）

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
