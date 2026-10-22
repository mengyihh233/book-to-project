// 【本题说明开始】
// 第3章习题17：支持负数与大位移的凯撒替换
//
// 题目：输入两行：文本、signed 64-bit位移。字母循环移动，输出字母统一大写，其他字符不变。负位移向前移动，任意大整数先对26归一化，不能通过对最小负数取反来实现。
// 实现什么：encodeCaesarCipher(const std::string& text, long long shift)
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
inline char lower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upper(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline bool letter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline bool vowel(char c) { return std::string("aeiou").find(lower(c))!=std::string::npos; }

// 本题要实现的接口（声明已给出）。
std::string encodeCaesarCipher(const std::string& text, long long shift);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto text=line(),amount=line();
        endInput();
        long long shift=0;
        const auto parsed=std::from_chars(amount.data(),amount.data()+amount.size(),shift);
        if(parsed.ec!=std::errc{
        }
        || parsed.ptr!=amount.data()+amount.size()) throw std::invalid_argument("expected signed 64-bit shift");
        std::cout<<encodeCaesarCipher(text,shift)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string encodeCaesarCipher(const std::string& text, long long shift) {
    /* BEGIN 1：encodeCaesarCipher */
    // 提示：先把位移对 26 归一化成非负数（注意最小负数不能直接取反），再循环移动，字母统一大写。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
