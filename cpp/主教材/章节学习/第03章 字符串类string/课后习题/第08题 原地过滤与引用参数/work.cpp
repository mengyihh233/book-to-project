// 【本题说明开始】
// 第3章习题8：原地过滤与引用参数
//
// 题目：输入两行：原字符串、删除字符集。通过引用原地修改原字符串，返回void；输出修改结果。删除集按值复制以正确处理两个实参引用同一字符串的情形。
// 实现什么：removeCharactersInPlace(std::string& str, std::string remove)
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
void removeCharactersInPlace(std::string& str, std::string remove);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto str=line();
        const auto remove=line();
        endInput();
        removeCharactersInPlace(str,remove);
        std::cout << str << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void removeCharactersInPlace(std::string& str, std::string remove) {
    /* BEGIN 1：removeCharactersInPlace */
    // 提示：用读、写两个下标原地压缩，保留的字符写到 write 位置，最后 resize；删除集是按值传入的。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
