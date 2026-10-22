// 【本题说明开始】
// 第2章习题4：风寒指数函数与输入约束
//
// 题目：实现windChill(t,v)。输入两个有限数：华氏温度t和英里/小时风速v。t≤40且v≥0；v=0时结果为t，其余用35.74+0.6215t−35.75×v^0.16+0.42
//   75t×v^0.16计算体感温度。域外输入或非有限结果报错。输出一个数值。
// 实现什么：double windChill(double t,double v)
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
double windChill(double t,double v);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        double t = readFinite();
        double v = readFinite();
        ensureEnd();
        std::cout << windChill(t, v) << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
double windChill(double t,double v) {
    /* BEGIN 1：实现windChill */
    // 先处理无风和温度/风速的合法范围。
    // 按题目给出的公式计算；检查最终数值是否有限。
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
