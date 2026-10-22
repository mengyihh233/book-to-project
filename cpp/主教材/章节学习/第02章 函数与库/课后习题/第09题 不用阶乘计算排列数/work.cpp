// 【本题说明开始】
// 第2章习题9：不用阶乘计算排列数
//
// 题目：实现permutations(n,k)，直接计算n×(n−1)×…×(n−k+1)，不先分别计算阶乘。输入两个整数n k，满足0≤k≤n≤1000000；k=0时空乘积为1。main输
//   出结果，若结果超出有符号64位整数范围则报错。
// 实现什么：long long permutations(long long n,long long k)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

// 函数声明已给出；本题只补下方BEGIN / END之间的函数体。
long long permutations(long long n,long long k);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        long long n = readInteger();
        long long k = readInteger();
        ensureEnd();
        std::cout << permutations(n, k) << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
long long permutations(long long n,long long k) {
    /* BEGIN 1：实现permutations */
    // 从1开始，循环连乘所需的k个因子；k=0时应返回1。
    // 检查参数范围与long long乘法溢出，不使用阶乘比值。
    // 完成后删除下面的占位throw，并按函数返回类型返回结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// #region 给定的输入检查辅助：本题不用修改
double readFinite() {
    double value;
    if (!(std::cin >> value) || !std::isfinite(value))
        throw std::invalid_argument("输入应为有限实数");
    return value;
}

long long readInteger() {
    long long value;
    if (!(std::cin >> value))
        throw std::invalid_argument("输入应为整数");
    return value;
}

void ensureEnd() {
    std::cin >> std::ws;
    if (!std::cin.eof())
        throw std::invalid_argument("输入含多余数据");
}
// #endregion
