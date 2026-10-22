// 【本题说明开始】
// 第2章习题2：引用参数返回英尺与英寸
//
// 题目：读入非负米数m（0到10^9），用引用参数同时返回整数英尺数feet与剩余英寸inches。1英尺=12英寸，1英寸=0.0254米；feet取完整英尺，余量换算为英寸。输出feet 
//   inches两个数值，以空格分隔。本题按相对误差1e-6、绝对误差1e-12比较，不强求固定小数位。
// 实现什么：void metersToFeetInches(double meters,long long&feet,double&inches)
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
void metersToFeetInches(double meters,long long&feet,double&inches);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        double m = readFinite();
        ensureEnd();
        long long feet = 0;
        double inches = 0;
        metersToFeetInches(m, feet, inches);
        std::cout << feet << " " << inches << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
void metersToFeetInches(double meters,long long&feet,double&inches) {
    /* BEGIN 1：实现metersToFeetInches */
    // 计算完整英尺数，再将剩余长度换算为英寸。
    // 通过feet、inches两个引用参数将结果带回；输入超出题目范围时抛出异常。
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
