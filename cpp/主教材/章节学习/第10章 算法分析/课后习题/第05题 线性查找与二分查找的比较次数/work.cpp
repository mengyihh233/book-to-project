// 【本题说明开始】
// 第10章 · 习题5：线性查找与二分查找的比较次数
//
// 题目：不测时间，改数「比较了多少次」：同一批查询，线性查找和二分查找各比几次。
// 实现什么：`linearComparisons()` 与 `binaryComparisons()` 两个计数函数。
// 写在哪里：只补下方 BEGIN 1（线性查找的计数）与 BEGIN 2（二分查找的计数）之间的代码。
// 文本格式：每行 `值 线性=a 二分=b`；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

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
    // @@1@@
    /* END 1 */
}

// 折半查找，返回比较次数。
int binaryComparisons(const std::vector<long long>& values, long long key) {
    /* BEGIN 2 */
    // @@2@@
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
