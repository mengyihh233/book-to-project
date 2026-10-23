#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int linearComparisons(const std::vector<long long>& values, long long key);

int binaryComparisons(const std::vector<long long>& values, long long key);

// 从下标 0 开始逐个比较，返回比较次数（找不到就是 n 次）。
int linearComparisons(const std::vector<long long>& values, long long key) {
    /* BEGIN 1 */
    int count = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        ++count;
        if (values[i] == key) return count;
    }
    return count;
    /* END 1 */
}

// 折半查找，返回比较次数。
int binaryComparisons(const std::vector<long long>& values, long long key) {
    /* BEGIN 2 */
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;
    int count = 0;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        ++count;
        if (values[static_cast<std::size_t>(mid)] == key) return count;
        if (values[static_cast<std::size_t>(mid)] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return count;
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("元素个数必须在 1 到 1000 之间");
        }

        std::vector<long long> values(static_cast<std::size_t>(n));
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> values[static_cast<std::size_t>(i)])) {
                throw std::invalid_argument("数字个数不足");
            }
            if (i > 0 && values[static_cast<std::size_t>(i)] < values[static_cast<std::size_t>(i - 1)]) {
                throw std::invalid_argument("数组必须升序排列");
            }
        }

        int q = 0;
        if (!(std::cin >> q) || q < 0 || q > 1000) {
            throw std::invalid_argument("查询个数必须在 0 到 1000 之间");
        }

        std::vector<long long> queries(static_cast<std::size_t>(q));
        for (int i = 0; i < q; ++i) {
            if (!(std::cin >> queries[static_cast<std::size_t>(i)])) {
                throw std::invalid_argument("查询值个数不足");
            }
        }

        for (long long key : queries) {
            std::cout << key << " 线性=" << linearComparisons(values, key)
                      << " 二分=" << binaryComparisons(values, key) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
