// 【本题说明开始】
// 第4章 · 习题9：忽略大小写删除指定字母
//
// 题目：标准输入三行：输入文件名、全新输出文件名、要删除的字母集合。集合仅允许ASCII英文字母，可为空、可重复，不区分大小写；删除大小写两类，其他字符和换行逐字节保留。结果写真实输出文件，正
//   常标准输出（cout）为空。
// 实现什么：std::string banishLetters(const std::string& text, const std::string& letters)
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
std::string banishLetters(const std::string& text, const std::string& letters);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string input,output,letters,extra;
    if(!book_input::logicalLine(std::cin,input)||!book_input::logicalLine(std::cin,output)||!book_input::logicalLine(std::cin,letters)||book_input::logicalLine(std::cin,extra)) return 2;
    try {
        auto text=banishLetters(readAsciiFile(input),letters);
        writeNewFile(output,text);
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string banishLetters(const std::string& text, const std::string& letters) {
    /* BEGIN 1：banishLetters */
    // 提示：先把字母集合统一成小写，再逐字符判断：转小写后命中集合就跳过，否则原样保留。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
