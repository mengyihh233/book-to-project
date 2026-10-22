# 第10章 项目：排序代价统计 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：排序代价统计
// 同一个数组，分别统计选择排序的比较次数、插入排序的元素移动次数。
#include <iostream>
#include <vector>

namespace {

long long selectionComparisons(std::vector<int> data) {
    const int n = static_cast<int>(data.size());
    long long compares = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            ++compares;                       // 内层每比较一次就记一次
            if (data[j] < data[minIndex]) minIndex = j;
        }
        if (minIndex != i) std::swap(data[i], data[minIndex]);
    }
    return compares;
}

long long insertionMoves(std::vector<int> data) {
    const int n = static_cast<int>(data.size());
    long long moves = 0;
    for (int i = 1; i < n; ++i) {
        const int value = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > value) {   // 严格大于才移动：相等时稳定
            data[j + 1] = data[j];
            --j;
            ++moves;
        }
        data[j + 1] = value;
    }
    return moves;
}

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    std::vector<int> data;
    data.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) {
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        data.push_back(value);
    }
    std::cout << "选择比较 " << selectionComparisons(data) << "\n";
    std::cout << "插入移动 " << insertionMoves(data) << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `5` + `5 4 3 2 1` → 选择 10，插入移动 10
- [ ] `5` + `1 2 3 4 5` → 选择 10，插入移动 **0**（已排好序，一次都不移）
- [ ] `6` + `6 5 4 3 2 1` → 选择 15，插入移动 15
- [ ] `1` + `7` → 都是 0
- [ ] `4` + `2 2 1 1` → 选择 6，插入移动 4（相等不移动）
- [ ] `3` + `3 1 2` → 选择 3，插入移动 2
- [ ] `0` → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
