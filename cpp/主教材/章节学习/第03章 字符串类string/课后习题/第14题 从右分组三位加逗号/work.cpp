// 【本题说明开始】
// 第3章习题14：从右分组三位加逗号
//
// 题目：输入一行非空十进制数字字符串，从右侧每三位插入逗号。前导零保留；不接受正负号、小数点、原有逗号或空格。按字符处理，不转换为有位数限制的整数。
// 实现什么：addCommas(const std::string& digits)
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
std::string addCommas(const std::string& digits);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto text=line();
        endInput();
        std::cout<<addCommas(text)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string addCommas(const std::string& digits) {
    /* BEGIN 1：addCommas */
    // 提示：从右往左每 3 位插一个逗号，最前面不再加；按字符处理，不要转成整数。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
