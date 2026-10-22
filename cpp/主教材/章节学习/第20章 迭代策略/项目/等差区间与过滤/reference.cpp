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
