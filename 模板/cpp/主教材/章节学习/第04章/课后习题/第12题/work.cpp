// 【本题说明开始】
// 第4章 · 习题12：基于整行读取实现getReal与getLine
//
// 题目：先逐行读取实数，非法行提示写cerr并继续重试；合法后再读取一行标签。输出两行：格式化实数、原标签（可为空或含空格）。任何必需行遇EOF，退出2且标准输出（cout）为空，避免无限重试
//   或半份结果。保留getReal(prompt="")和getLine(prompt="")接口；后者通过getline读取整行，不跳过合法空行。
// 实现什么：std::string realToString(double value)、std::string getLine(const std::string& prompt)、double getReal(const std::string& prompt)
// 写在哪里：只补下方 BEGIN 1、BEGIN 2、BEGIN 3 之间的函数体。
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

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline double stringToReal(const std::string& text) {
    std::istringstream in(text);in.imbue(std::locale::classic());double value;
    if(!(in>>value) || !std::isfinite(value)) throw std::invalid_argument("invalid real");
    in>>std::ws;
    if(!in.eof()) throw std::invalid_argument("trailing characters");
    return value;
}

// 本题要实现的接口（声明已给出）。
std::string realToString(double value);
std::string getLine(const std::string& prompt="");
double getReal(const std::string& prompt="");

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        double number=getReal("Real: ");
        std::string label=getLine("Label: ");
        std::cout<<realToString(number)<<'\n'<<label<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 3 个函数体。

std::string realToString(double value) {
    /* BEGIN 1：realToString */
    // 提示：把 double 按题目要求格式化输出，拒绝非有限值。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

std::string getLine(const std::string& prompt) {
    /* BEGIN 2：getLine */
    // 提示：打印提示后循环读整行，空行是合法标签；遇 EOF 抛异常。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}

double getReal(const std::string& prompt) {
    /* BEGIN 3：getReal */
    // 提示：同样循环读整行，非法就写 cerr 后重试，直到合法或 EOF。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 3 */
}
