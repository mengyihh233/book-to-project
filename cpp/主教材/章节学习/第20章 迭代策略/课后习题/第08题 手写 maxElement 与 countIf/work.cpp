// 【本题说明开始】
// 第20章 · 习题8：手写 maxElement 与 countIf
//
// 题目：不看 `<algorithm>`，自己写两个函数模板：找最大元素的迭代器、统计满足谓词的元素个数。
// 实现什么：`maxElement()` 与 `countIf()` 两个函数模板。
// 写在哪里：只补下方 BEGIN 1（maxElement 模板）与 BEGIN 2（countIf 模板）之间的代码。
// 文本格式：`max = 值 at 下标` 加每条查询的计数；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 返回区间内最大元素的迭代器；空区间返回 end。并列取第一个。
template <typename IterType>
IterType maxElement(IterType begin, IterType end) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

// 统计 pred(*it) 为真的元素个数。
template <typename IterType, typename Predicate>
int countIf(IterType begin, IterType end, Predicate pred) {
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
        }

        int q = 0;
        if (!(std::cin >> q) || q < 0 || q > 1000) {
            throw std::invalid_argument("查询条数必须在 0 到 1000 之间");
        }

        // 先把命令全部读进来校验，再一次输出——半份结果同样是错的。
        struct Query {
            std::string name;
            bool hasArg;
            long long arg;
        };
        std::vector<Query> queries;
        for (int i = 0; i < q; ++i) {
            Query query;
            query.hasArg = false;
            query.arg = 0;
            if (!(std::cin >> query.name)) throw std::invalid_argument("查询命令缺失");
            const bool compares = query.name == "gt" || query.name == "lt" || query.name == "eq";
            const bool plain = query.name == "even" || query.name == "odd"
                            || query.name == "pos" || query.name == "neg";
            if (!compares && !plain) {
                throw std::invalid_argument("未知命令：" + query.name);
            }
            if (compares) {
                if (!(std::cin >> query.arg)) {
                    throw std::invalid_argument("比较命令缺少参数：" + query.name);
                }
                query.hasArg = true;
            }
            queries.push_back(query);
        }

        const auto largest = maxElement(values.begin(), values.end());
        std::cout << "max = " << *largest << " at " << (largest - values.begin()) << '\n';

        for (const Query& query : queries) {
            if (query.name == "even") {
                std::cout << "even = " << countIf(values.begin(), values.end(),
                    [](long long v) { return v % 2 == 0; }) << '\n';
            } else if (query.name == "odd") {
                std::cout << "odd = " << countIf(values.begin(), values.end(),
                    [](long long v) { return v % 2 != 0; }) << '\n';
            } else if (query.name == "pos") {
                std::cout << "pos = " << countIf(values.begin(), values.end(),
                    [](long long v) { return v > 0; }) << '\n';
            } else if (query.name == "neg") {
                std::cout << "neg = " << countIf(values.begin(), values.end(),
                    [](long long v) { return v < 0; }) << '\n';
            } else if (query.name == "gt") {
                const long long k = query.arg;
                std::cout << "gt " << k << " = " << countIf(values.begin(), values.end(),
                    [k](long long v) { return v > k; }) << '\n';
            } else if (query.name == "lt") {
                const long long k = query.arg;
                std::cout << "lt " << k << " = " << countIf(values.begin(), values.end(),
                    [k](long long v) { return v < k; }) << '\n';
            } else {
                const long long k = query.arg;
                std::cout << "eq " << k << " = " << countIf(values.begin(), values.end(),
                    [k](long long v) { return v == k; }) << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
