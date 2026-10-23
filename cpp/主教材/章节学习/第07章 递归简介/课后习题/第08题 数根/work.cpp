// 【本题说明开始】
// 第7章 · 习题8：数根
//
// 题目：读入 n 个非负整数，用递归反复求数位和，直到剩下一位（数根）。
// 实现什么：`digitalRoot(x)` 的递归 + `main` 的循环。
// 写在哪里：只补下方 BEGIN 1（递归/迭代函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每行一个数根；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>

int digitalRoot(long long x) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("个数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
