// 【本题说明开始】
// 第3章习题11：忽略标点的句子回文
//
// 题目：单行入口输入一个句子，只比较ASCII字母，忽略标点、数字和大小写，输出true/false；空串或没有字母的字符串为true。另有interactive.cpp保留原题连续读句子、空行结束的交互流程，不能混用两种输入格式。
// 实现什么：isSentencePalindrome(const std::string& str)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <stdexcept>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline bool sentenceLetter(char c) { return (c>='a' && c<='z') || (c>='A' && c<='Z'); }
inline char sentenceLower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }

// 本题要实现的接口（声明已给出）。
bool isSentencePalindrome(const std::string& str);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto s=line();
        endInput();
        std::cout<<(isSentencePalindrome(s) ? "true" : "false")<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

bool isSentencePalindrome(const std::string& str) {
    /* BEGIN 1：isSentencePalindrome */
    // 提示：左右两个下标向中间走，各自跳过非字母，再比小写；串里没有字母时返回 true。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
