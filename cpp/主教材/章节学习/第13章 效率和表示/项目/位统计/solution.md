# 第13章 项目：位统计 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：位统计
// 对一组非负整数统计：全部按位或、按位与、二进制中 1 的总个数、最大值的最高位位置。
#include <iostream>

namespace {

int bitCount(unsigned value) {
    int count = 0;
    while (value) {
        value &= value - 1;      // 每次消掉最低位的 1
        ++count;
    }
    return count;
}

int highestBit(unsigned value) {
    if (value == 0) return -1;   // 0 没有最高位
    int pos = 0;
    while (value >>= 1) ++pos;
    return pos;
}

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    unsigned bitsOr = 0;
    unsigned bitsAnd = 0xFFFFFFFFu;   // 与运算的单位元是全 1
    long long ones = 0;
    unsigned maxValue = 0;
    for (int i = 0; i < n; ++i) {
        long long raw = 0;
        if (!(std::cin >> raw)) {
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        if (raw < 0) {
            std::cerr << "只接受非负整数\n";
            return 2;
        }
        const unsigned value = static_cast<unsigned>(raw);
        bitsOr |= value;
        bitsAnd &= value;
        ones += bitCount(value);
        if (i == 0 || value > maxValue) maxValue = value;
    }
    std::cout << "按位或 " << bitsOr << "\n";
    std::cout << "按位与 " << bitsAnd << "\n";
    std::cout << "1的个数 " << ones << "\n";
    std::cout << "最高位 " << highestBit(maxValue) << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `3` + `1 2 4` → 或 7，与 0，1的个数 3，最高位 2
- [ ] `1` + `0` → 或 0，与 0，1的个数 0，最高位 **-1**
- [ ] `2` + `5 3` → 或 7，与 1，1的个数 4（101 + 011），最高位 2
- [ ] `2` + `8 8` → 或 8，与 8，1的个数 2，最高位 3
- [ ] `3` + `2147483647 0 1` → 或 2147483647，与 0，1的个数 **32**，最高位 30
- [ ] `0` → 返回 2
- [ ] `2` + `-1 5` → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
