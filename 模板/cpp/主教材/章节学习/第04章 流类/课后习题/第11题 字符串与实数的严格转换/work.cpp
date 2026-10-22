// 【本题说明开始】
// 第4章 · 习题11：字符串与实数的严格转换
//
// 题目：输入一行实数文本，调用stringToReal后再用realToString输出一行。允许首尾空白、小数和十进制科学计数法，必须整行解析成功；拒绝非有限值、溢出与尾部垃圾。classi
//   c locale固定小数点为.。输出以max_digits10有效数字保证double往返，0.1可能显示为0.10000000000000001，并非小数计算出错。此精度策略是教学约
//   定。
// 实现什么：double stringToReal(const std::string& text)、std::string realToString(double value)
// 写在哪里：只补下方 BEGIN 1、BEGIN 2 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/input_line.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>

// 本题要实现的接口（声明已给出）。
double stringToReal(const std::string& text);
std::string realToString(double value);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string text,extra;
    if(!book_input::logicalLine(std::cin,text)||book_input::logicalLine(std::cin,extra)) return 2;
    try {
        std::cout<<realToString(stringToReal(text))<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 2 个函数体。

double stringToReal(const std::string& text) {
    /* BEGIN 1：stringToReal */
    // 提示：先去掉首尾空白，再用 classic locale 整行解析，解析后不能有剩余字符，并拒绝非有限值。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

std::string realToString(double value) {
    /* BEGIN 2：realToString */
    // 提示：用 ostringstream 配 classic locale 和足够精度输出，保证往返不失真。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}
