// 【本题说明开始】
// 第2章习题3：四舍五入到最近int
//
// 题目：实现roundToNearestInt函数，读入一个有限实数，四舍五入到最近的int；正负半整数均向远离零方向取整，例如2.5→3、-2.5→-3。结果不能超出int范围。main读入
//   、调用函数并输出一个整数。
// 实现什么：int roundToNearestInt(double x)
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
int roundToNearestInt(double x);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        double x = readFinite();
        ensureEnd();
        std::cout << roundToNearestInt(x) << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
int roundToNearestInt(double x) {
    /* BEGIN 1：实现roundToNearestInt */
    // 分别考虑正数与负数恰好落在0.5的情况。
    // 返回最近int；先确认舍入后的值没有超出int范围。
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
