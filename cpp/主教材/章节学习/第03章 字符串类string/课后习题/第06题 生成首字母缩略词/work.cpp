// 【本题说明开始】
// 第3章习题6：生成首字母缩略词
//
// 题目：输入一行，将每个连续ASCII字母段的首字母转大写后连接。连字符、空格、数字和标点都是分隔符，可位于任意位置；不跳过of、the等词。
// 实现什么：acronym(const std::string& phrase)
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
inline bool asciiLetter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }

// 本题要实现的接口（声明已给出）。
std::string acronym(const std::string& phrase);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line();
        endInput();
        std::cout << acronym(str) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string acronym(const std::string& phrase) {
    /* BEGIN 1：acronym */
    // 提示：遍历字符，遇到字母且前一个不是字母时，把这个字母转大写后追加。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
