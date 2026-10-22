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
