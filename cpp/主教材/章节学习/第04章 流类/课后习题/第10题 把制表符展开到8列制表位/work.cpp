// 【本题说明开始】
// 第4章 · 习题10：把制表符展开到8列制表位
//
// 题目：标准输入两行：输入文件名、全新输出文件名。每行从0列开始，TAB补空格至下一个8列边界；恰好在边界时补8个空格。LF/CR重置列，CRLF逐字节保留。其他ASCII控制字符原样保留并按
//   一个显示列计数，不模拟终端退格。输出写真实文件，标准输出（cout）为空。
// 实现什么：std::string expandTabs(const std::string& text)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/input_line.h"
#include "../../../../教学辅助/file_lesson.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cstdint>
#include <charconv>
#include <array>

// 本题要实现的接口（声明已给出）。
std::string expandTabs(const std::string& text);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string input,output,extra;
    if(!book_input::logicalLine(std::cin,input)||!book_input::logicalLine(std::cin,output)||book_input::logicalLine(std::cin,extra)) return 2;
    try {
        auto text=expandTabs(readAsciiFile(input));
        writeNewFile(output,text);
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string expandTabs(const std::string& text) {
    /* BEGIN 1：expandTabs */
    // 提示：维护当前列号；遇到 TAB 补 8 - col % 8 个空格，遇到 CR 或 LF 把列号归零。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
