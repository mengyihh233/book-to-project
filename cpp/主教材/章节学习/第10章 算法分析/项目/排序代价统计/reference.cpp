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
