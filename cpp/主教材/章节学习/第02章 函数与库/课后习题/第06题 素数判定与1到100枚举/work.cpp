// 【本题说明开始】
// 第2章习题6：素数判定与1到100枚举
//
// 题目：素数是大于 1、只能被 1 和它自己整除的整数。1 不是素数，0 和负数也不是。
// 实现什么：bool isPrime(int n)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <stdexcept>

// 函数声明已给出；本题只补下方 BEGIN 1 / END 1 之间的函数体。
bool isPrime(int n);
void ensureEnd();

// 给定主程序：枚举 1..100，调用 isPrime，按从小到大输出。
int main() {
    try {
        ensureEnd();
        bool first = true;
        for (int n = 1; n <= 100; ++n) {
            if (isPrime(n)) {
                if (!first) std::cout << " ";
                std::cout << n;
                first = false;
            }
        }
        std::cout << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义 main 或函数签名。
bool isPrime(int n) {
    /* BEGIN 1：实现 isPrime */
    // 第1步：先排除 n ≤ 1 的情况（1 不是素数，0 和负数也不是）。
    // 第2步：从 2 开始循环，寻找能整除 n 的因子。
    // 第3步：找到因子就返回 false；循环结束都没找到才返回 true。
    // 完成后删除下面的占位 throw，并按函数返回类型返回结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// #region 给定的输入检查辅助：本题不用修改
void ensureEnd() {
    std::cin >> std::ws;
    if (!std::cin.eof())
        throw std::invalid_argument("输入含多余数据");
}
// #endregion
