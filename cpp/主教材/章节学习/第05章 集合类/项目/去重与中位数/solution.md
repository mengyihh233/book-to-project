# 第5章 项目：去重与中位数 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：去重与中位数
// 读 N 个整数，去重排序后输出：不同值个数、中位数（1 位小数）、最小、最大。
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "N 必须在 1 到 100000 之间\n";
        return 2;
    }

    std::vector<int> values;
    values.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) {          // 数量不够就是错，不拿默认值凑
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        values.push_back(value);
    }

    // unique 只去掉“相邻”的重复，所以必须先排序
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    const std::size_t count = values.size();
    double median = 0.0;
    if (count % 2 == 1) {
        median = static_cast<double>(values[count / 2]);
    } else {
        // 两个中间值相加可能溢出 int，先转 double 再除
        median = (static_cast<double>(values[count / 2 - 1]) + static_cast<double>(values[count / 2])) / 2.0;
    }

    std::cout << "不同 " << count << "\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "中位数 " << median << "\n";
    std::cout << "最小 " << values.front() << "\n";
    std::cout << "最大 " << values.back() << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `5` + `3 1 3 2 9` → 不同 4，中位数 2.5，最小 1，最大 9
- [ ] `1` + `7` → 不同 1，中位数 7.0
- [ ] `4` + `5 5 5 5` → 不同 1，中位数 5.0
- [ ] `2` + `1 2` → 中位数 1.5
- [ ] `3` + `-5 -1 -3` → 排序后 -5 -3 -1，中位数 -3.0
- [ ] `0` → 返回 2，`stdout` 为空
- [ ] `3` + 只有两个数 → 返回 2
- [ ] 中位数是 `2.5` 不是 `2.50`，也不是 `2`

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
