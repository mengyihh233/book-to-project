// 【本题说明开始】
// 第3章习题2：去除首尾空白
//
// 题目：输入一行，删除首尾ASCII空白，保留内部空白。输出结果原样保留。空白集合为SP、TAB、CR、LF、VT、FF；换行是输入行分隔符，函数本身也支持LF。
// 实现什么：trim(const std::string& str)
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
inline bool asciiSpace(char c) { return c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\v' || c=='\f'; }

// 本题要实现的接口（声明已给出）。
std::string trim(const std::string& str);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line();
        endInput();
        std::cout << trim(str) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string trim(const std::string& str) {
    /* BEGIN 1：trim */
    // 提示：从两端各向内跳过空白字符，直到不是空白为止；整串都是空白时返回空串。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
