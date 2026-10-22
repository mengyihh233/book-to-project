// 【本题说明开始】
// 第2章习题1：用函数完成温标换算
//
// 题目：读入一个有限摄氏温度C，按F=C×9/5+32计算华氏温度。将换算写成celsiusToFahrenheit函数；main只负责读入、调用、输出。输入只有一个数，不接受多余数据；结果必
//   须有限。
// 实现什么：double celsiusToFahrenheit(double c)
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
double celsiusToFahrenheit(double c);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        double c = readFinite();
        ensureEnd();
        std::cout << celsiusToFahrenheit(c) << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
double celsiusToFahrenheit(double c) {
    /* BEGIN 1：实现celsiusToFahrenheit */
    // 将摄氏温度按题目公式换算为华氏温度，返回计算结果。
    // 对非有限结果抛出异常；不要在换算函数内读入或输出。
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
