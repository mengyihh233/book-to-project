// 【本题说明开始】
// 第7章 · 习题9：组合数
//
// 题目：读入 n 组 `n k`，用递归算组合数 C(n, k)。
// 实现什么：`comb(n, k)` 的递归体 + `main` 的循环。
// 写在哪里：只补下方 BEGIN 1（递归函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每行一个组合数；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>

long long comb(int n, int k) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int m = 0;
        if (!(std::cin >> m) || m < 1 || m > 50) {
            throw std::invalid_argument("组数必须在 1 到 50 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
