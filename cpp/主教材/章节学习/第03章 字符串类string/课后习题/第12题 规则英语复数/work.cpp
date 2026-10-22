// 【本题说明开始】
// 第3章习题12：规则英语复数
//
// 题目：输入一个非空、全小写ASCII单词。严格按原题三条简化规则生成复数：s/x/z/ch/sh加es；辅音字母+y改ies；否则加s。不会查词典或处理不规则词，输入约束为教学约定。
// 实现什么：createRegularPlural(const std::string& word)
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
std::string createRegularPlural(const std::string& word);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto s=line();
        endInput();
        std::cout<<createRegularPlural(s)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string createRegularPlural(const std::string& word) {
    /* BEGIN 1：createRegularPlural */
    // 提示：先看词尾：ch 或 sh 或 s/x/z 加 es；辅音字母加 y 改成 ies；其余直接加 s。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
