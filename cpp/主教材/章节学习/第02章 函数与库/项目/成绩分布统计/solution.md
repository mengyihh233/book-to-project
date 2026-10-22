# 第2章 项目：成绩分布统计 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：成绩分布统计
// 强制拆成三个函数：读入、统计、输出。main 只做串接。
#include <iomanip>
#include <iostream>
#include <vector>

namespace {

struct Stats {
    double mean;
    double passRate;
    double excellentRate;
    int high;
    int low;
};

bool readScores(std::vector<int>& scores) {
    int n = 0;
    if (!(std::cin >> n)) return false;
    if (n < 1 || n > 1000) return false;
    scores.clear();
    scores.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) return false;   // 行数不足也算错，不拿默认值凑
        if (value < 0 || value > 100) return false;
        scores.push_back(value);
    }
    return true;
}

Stats summarize(const std::vector<int>& scores) {
    long long sum = 0;
    int pass = 0, excellent = 0;
    int high = scores.front(), low = scores.front();
    for (int value : scores) {
        sum += value;
        if (value >= 60) ++pass;
        if (value >= 90) ++excellent;
        if (value > high) high = value;
        if (value < low) low = value;
    }
    // 整数除法会把平均分截断，先转 double 再除
    const double total = static_cast<double>(scores.size());
    return Stats{static_cast<double>(sum) / total,
                 pass * 100.0 / total,
                 excellent * 100.0 / total,
                 high, low};
}

void print(const Stats& stats) {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "平均 " << stats.mean << "\n";
    std::cout << "及格率 " << stats.passRate << "%\n";
    std::cout << "优秀率 " << stats.excellentRate << "%\n";
    std::cout << "最高 " << stats.high << "\n";
    std::cout << "最低 " << stats.low << "\n";
}

}  // namespace

int main() {
    std::vector<int> scores;
    if (!readScores(scores)) {
        std::cerr << "成绩数据不合法\n";
        return 2;
    }
    print(summarize(scores));
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `5` + `90 80 70 60 50` → 平均 70.0，及格率 80.0%，优秀率 20.0%，最高 90，最低 50
- [ ] `1` + `100` → 平均 100.0，及格率 100.0%，优秀率 100.0%
- [ ] `1` + `0` → 平均 0.0，及格率 0.0%，优秀率 0.0%
- [ ] `0` → 返回 2，`stdout` 为空
- [ ] `1` + `101` → 返回 2
- [ ] `3` + 只有两行成绩 → 返回 2
- [ ] 全部 60 分 → 及格率 100.0%，优秀率 0.0%（边界值要算对）
- [ ] 平均分是 `70.0` 而不是 `70` 或 `70.00`

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
