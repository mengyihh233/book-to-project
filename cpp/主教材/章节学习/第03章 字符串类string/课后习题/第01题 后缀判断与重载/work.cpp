// 【本题说明开始】
// 第3章习题1：后缀判断与重载
//
// 题目：输入两行：原字符串、后缀。输出true/false。函数另有char后缀重载，见tests.cpp；交互入口统一按字符串读入，不把单字符字符串误认为char类型。
// 实现什么：endsWith(const std::string& str, const std::string& suffix)、endsWith(const std::string& str, char suffix)
// 写在哪里：只补下方 BEGIN 1、BEGIN 2 之间的函数体。
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
bool endsWith(const std::string& str, const std::string& suffix);
bool endsWith(const std::string& str, char suffix);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line(),suffix=line();
        endInput();
        std::cout << (endsWith(str,suffix) ? "true" : "false") << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 2 个函数体。

bool endsWith(const std::string& str, const std::string& suffix) {
    /* BEGIN 1：endsWith */
    // 提示：先比长度：后缀比原串长一定不匹配，空后缀算匹配；否则从末尾逐位比较。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

bool endsWith(const std::string& str, char suffix) {
    /* BEGIN 2：endsWith */
    // 提示：char 版：可以构造一个单字符串复用上面的实现，也可以只比最后一个字符。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}
