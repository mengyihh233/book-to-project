# 第20章 项目：等差区间与过滤 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：等差区间与过滤
// 用一个可迭代的 Range 类生成等差数列，range-for 遍历 + 谓词筛选，
// 过程中直接统计和/个数/最大/最小，不把整个序列存进容器。
#include <iostream>
#include <string>

class Range {
public:
    struct iterator {
        long long value;
        long long step;
        long long index;
        long long count;

        long long operator*() const { return value; }
        iterator& operator++() {
            ++index;
            value += step;
            return *this;
        }
        bool operator!=(const iterator& other) const { return index != other.index; }
    };

    Range(long long start, long long step, long long count)
        : start_(start), step_(step), count_(count) {}

    iterator begin() const { return iterator{start_, step_, 0, count_}; }
    iterator end() const { return iterator{start_ + step_ * count_, step_, count_, count_}; }

private:
    long long start_;
    long long step_;
    long long count_;
};

bool keep(const std::string& strategy, long long v) {
    if (strategy == "all") return true;
    if (strategy == "even") return v % 2 == 0;
    if (strategy == "odd") return v % 2 != 0;
    if (strategy == "pos") return v > 0;
    if (strategy == "neg") return v < 0;
    return false;
}

int main() {
    long long start = 0, step = 0, count = 0;
    if (!(std::cin >> start >> step >> count)) {
        std::cerr << "需要三个整数：起点 步长 个数\n";
        return 2;
    }
    const long long kLimit = 1000000000LL;
    if (start < -kLimit || start > kLimit || step < -kLimit || step > kLimit) {
        std::cerr << "起点和步长的绝对值不能超过 10^9\n";
        return 2;
    }
    if (count < 0 || count > 100000) {
        std::cerr << "个数必须在 0 到 100000 之间\n";
        return 2;
    }

    std::string strategy;
    if (!(std::cin >> strategy)) {
        std::cerr << "缺少过滤策略\n";
        return 2;
    }
    if (strategy != "all" && strategy != "even" && strategy != "odd" &&
        strategy != "pos" && strategy != "neg") {
        std::cerr << "未知的过滤策略：" << strategy << "\n";
        return 2;
    }

    long long sum = 0, kept = 0;
    long long max_value = 0, min_value = 0;
    bool first = true;

    std::cout << "序列";
    for (long long v : Range(start, step, count)) {
        if (!keep(strategy, v)) continue;
        std::cout << ' ' << v;
        sum += v;
        ++kept;
        if (first) {
            max_value = min_value = v;
            first = false;
        } else {
            if (v > max_value) max_value = v;
            if (v < min_value) min_value = v;
        }
    }
    std::cout << "\n";

    std::cout << "和 " << sum << "\n";
    std::cout << "个数 " << kept << "\n";
    if (kept == 0) {
        std::cout << "最大 无\n";
        std::cout << "最小 无\n";
    } else {
        std::cout << "最大 " << max_value << "\n";
        std::cout << "最小 " << min_value << "\n";
    }
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] 上面那组输入 → `序列 15 25` / `和 40` / `个数 2` / `最大 25` / `最小 15`
- [ ] `-5 3 4` + `all` → `序列 -5 -2 1 4`，和 `-2`，最大 `4`，最小 `-5`
- [ ] `0 0 3` + `pos` → 只有 `序列`，和 0，个数 0
- [ ] `0 -7 5` + `neg` → `序列 -7 -14 -21 -28`，和 `-70`，最大 `-7`，最小 `-28`
- [ ] `999999937 1 3` + `all` → 和 `2999999814`（用 `int` 会算错）
- [ ] 策略写 `foo` → 返回 2，屏幕无输出
- [ ] 个数写 `-1` → 返回 2，屏幕无输出

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
