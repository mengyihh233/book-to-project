// 【本题说明开始】
// 第7章 · 习题6：递归调用次数
//
// 题目：用递归版 fib 计算第 n 项，并统计一共发生了多少次函数调用。
// 实现什么：`fibCounted(n)`（递归 + 计数）+ `main` 的输出格式。
// 写在哪里：只补下方 BEGIN 1（递归/迭代函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行 `n=.. fib=.. calls=..`；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>

long long calls = 0;

long long fibCounted(int n) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 24) {
            throw std::invalid_argument("n 必须在 0 到 24 之间");
        }
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
