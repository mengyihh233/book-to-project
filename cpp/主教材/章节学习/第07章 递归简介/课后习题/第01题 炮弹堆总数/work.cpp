// 【本题说明开始】
// 第7章 · 习题1：炮弹堆总数
//
// 题目：给定金字塔高度 n，求炮弹总数 1² + 2² + … + n²，必须用递归。
// 实现什么：`cannonball(n)` 的递归体 + `main` 的读入输出。
// 写在哪里：只补下方 BEGIN 1（递归函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行整数；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>

// 金字塔高度 n 的炮弹总数：1*1 + 2*2 + ... + n*n
long long cannonball(int n) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("高度必须在 1 到 1000 之间");
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
