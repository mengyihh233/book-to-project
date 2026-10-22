// 【本题说明开始】
// 第4章 · 习题5：拆分文件根名与扩展名
//
// 题目：第8题按原始输出精确比较，最后的换行也是结果一部分；其他题移除程序打印的一次末尾换行后比较，保留前后空格。提示应写cerr。
// 实现什么：std::string getRoot(const std::string& name)、std::string getExtension(const std::string& name)
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

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline std::string::size_type extensionPosition(const std::string& name) {
    auto slash=name.find_last_of("/\\");
    auto dot=name.find_last_of('.');
    return dot!=std::string::npos && (slash==std::string::npos || dot>slash) ? dot : std::string::npos;
}

// 本题要实现的接口（声明已给出）。
std::string getRoot(const std::string& name);
std::string getExtension(const std::string& name);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string name,extra;
    if(!book_input::logicalLine(std::cin,name) || book_input::logicalLine(std::cin,extra)) return 2;
    std::cout<<getRoot(name)<<'\n'<<getExtension(name)<<'\n';
}

// 实现位置：只填写下面 2 个函数体。

std::string getRoot(const std::string& name) {
    /* BEGIN 1：getRoot */
    // 提示：从末尾找最后一个点，而且它必须位于最后一个路径分隔符之后，才算扩展名的起点。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

std::string getExtension(const std::string& name) {
    /* BEGIN 2：getExtension */
    // 提示：根名是扩展名起点之前的部分；没有扩展名时整串都是根名，扩展名返回空串。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}
