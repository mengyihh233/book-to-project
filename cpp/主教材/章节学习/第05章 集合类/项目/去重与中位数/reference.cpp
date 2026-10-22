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
