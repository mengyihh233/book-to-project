// 【本题说明开始】
// 第11章 · 习题7：数组版归并排序
//
// 题目：读入 n 个整数，用归并排序（数组 + 下标）升序输出。
// 实现什么：`mergeSort`（数组 + 下标 + 临时缓冲区）+ `main` 的读入输出。
// 写在哪里：只补下方 BEGIN 1（要实现的函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行升序数组（空格分隔）；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>
#include <vector>

void mergeSort(int* data, int left, int right, int* buffer) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100000) {
            throw std::invalid_argument("n 必须在 1 到 100000 之间");
        }
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> data[i])) throw std::invalid_argument("数字个数不足");
        }
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
