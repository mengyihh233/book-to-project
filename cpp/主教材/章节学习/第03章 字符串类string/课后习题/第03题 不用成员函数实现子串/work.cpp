// 【本题说明开始】
// 第3章习题3：不用成员函数实现子串
//
// 题目：输入三行：原字符串、起始位置、字符数；第三行为ALL时调用省略字符数的重载默认参数。位置与数目限制0..1000000是验收约定。pos等于长度可返回空；pos大于长度报错；数目过大截到末尾，不能调用str.substr实现答案。
// 实现什么：substr(const std::string& str, std::size_t pos, std::size_t n=std::string::npos)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <algorithm>
#include <stdexcept>

// 本题要实现的接口（声明已给出）。
std::string substr(const std::string& str, std::size_t pos, std::size_t n=std::string::npos);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line();
        const auto pos=indexValue(line());
        const auto count=line();
        endInput();
        std::cout << (count=="ALL" ? substr(str,pos) : substr(str,pos,indexValue(count))) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string substr(const std::string& str, std::size_t pos, std::size_t n) {
    /* BEGIN 1：substr */
    // 提示：pos 大于长度时抛 out_of_range；n 超过剩余长度就截到末尾；不能调用 str.substr。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
