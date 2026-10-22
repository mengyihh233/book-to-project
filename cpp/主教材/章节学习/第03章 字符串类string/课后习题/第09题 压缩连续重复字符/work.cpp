// 【本题说明开始】
// 第3章习题9：压缩连续重复字符
//
// 题目：输入一行，连续的相同字符只保留一个，大小写敏感。不是删除所有重复出现的字符；重复空格也按字符压缩。
// 实现什么：removeDoubledLetters(const std::string& str)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <stdexcept>

// 本题要实现的接口（声明已给出）。
std::string removeDoubledLetters(const std::string& str);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto s=line();
        endInput();
        std::cout<<removeDoubledLetters(s)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string removeDoubledLetters(const std::string& str) {
    /* BEGIN 1：removeDoubledLetters */
    // 提示：与上一个保留的字符比较，不同才追加；第一个字符总是保留。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
