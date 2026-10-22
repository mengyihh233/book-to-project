// 【本题说明开始】
// 第3章习题13：数字序数词后缀
//
// 题目：输入一个0..9223372036854775807的整数，输出数字加st/nd/rd/th。11、12、13结尾优先用th；0按本区约定为0th。signed 64-bit范围是教学扩展，负数拒绝。
// 实现什么：createOrdinalForm(long long n)
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
std::string createOrdinalForm(long long n);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto text=line();
        endInput();
        long long value=0;
        const auto parsed=std::from_chars(text.data(),text.data()+text.size(),value);
        if(parsed.ec!=std::errc{
        }
        || parsed.ptr!=text.data()+text.size()) throw std::invalid_argument("expected signed 64-bit integer");
        std::cout<<createOrdinalForm(value)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string createOrdinalForm(long long n) {
    /* BEGIN 1：createOrdinalForm */
    // 提示：先看 n % 100，是 11、12、13 就一律 th；否则看 n % 10：1 用 st、2 用 nd、3 用 rd，其余 th。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
