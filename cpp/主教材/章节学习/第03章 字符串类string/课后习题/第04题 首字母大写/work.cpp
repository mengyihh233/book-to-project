// 【本题说明开始】
// 第3章习题4：首字母大写
//
// 题目：输入一行，仅将索引0处的字符（若是小写字母）转大写，其余ASCII大写字母转小写。非字母原样保留；不是寻找第一个字母。
// 实现什么：capitalize(std::string str)
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

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline char lowerAscii(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upperAscii(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }

// 本题要实现的接口（声明已给出）。
std::string capitalize(std::string str);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line();
        endInput();
        std::cout << capitalize(str) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string capitalize(std::string str) {
    /* BEGIN 1：capitalize */
    // 提示：先把整串的字母统一转小写，再把下标 0 的字符转大写；空串直接返回。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
