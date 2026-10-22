// 【本题说明开始】
// 第7章 · 习题2：递归求幂
//
// 题目：读入底数与指数，用递归算出整数幂（指数 0 结果为 1）。
// 实现什么：`power(base, exp)` 的递归体 + `main` 的读入输出。
// 写在哪里：只补下方 BEGIN 1（递归函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行整数；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>

long long power(long long base, int exp) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        long long base = 0;
        int exp = 0;
        if (!(std::cin >> base >> exp) || base < -10 || base > 10 || exp < 0 || exp > 18) {
            throw std::invalid_argument("底数要在 -10..10，指数要在 0..18");
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
