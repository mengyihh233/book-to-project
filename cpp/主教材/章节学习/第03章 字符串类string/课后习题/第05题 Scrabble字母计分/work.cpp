// 【本题说明开始】
// 第3章习题5：Scrabble字母计分
//
// 题目：输入一行，按原书表格累计字母分值；忽略大小写，非字母得0分。不计算双倍/三倍等棋盘奖励，空白棋子得0分。
// 实现什么：scrabbleScore(const std::string& word)
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
int scrabbleScore(const std::string& word);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line();
        endInput();
        std::cout << scrabbleScore(str) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

int scrabbleScore(const std::string& word) {
    /* BEGIN 1：scrabbleScore */
    // 提示：建立 A 到 Z 共 26 个分值的表，按字符查表累加；先统一成大写，非字母跳过。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
