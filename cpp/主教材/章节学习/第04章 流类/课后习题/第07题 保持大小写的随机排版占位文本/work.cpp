// 【本题说明开始】
// 第4章 · 习题7：保持大小写的随机排版占位文本
//
// 题目：正文范围：ASCII、最多16MiB；UTF-8中文路径支持不代表支持中文正文。文件不存在、输入缺行/多行、种子或字母集合错误、正文非ASCII、读写失败，退出2，stdout不发布部
//   分结果。空文件合法。源文件不能被修改。第9/10题使用独占创建，已有输出、同名输入、输出目录不存在均报错，不覆盖文件。
// 实现什么：std::string greekText(const std::string& text, std::uint32_t seed)
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

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline char randomLetter(std::mt19937& engine,bool upper) {
    // 拒绝法避免直接%26的余数偏差；mt19937输出为32位。
    std::uint32_t value;
    do {value=engine();} while(value>=4294967274U);
    return static_cast<char>((upper?'A':'a')+value%26);
}

// 本题要实现的接口（声明已给出）。
std::string greekText(const std::string& text, std::uint32_t seed);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string file,seedText,extra;
    if(!book_input::logicalLine(std::cin,file)||!book_input::logicalLine(std::cin,seedText)||book_input::logicalLine(std::cin,extra)) return 2;
    std::uint32_t seed=0;
    auto result=std::from_chars(seedText.data(),seedText.data()+seedText.size(),seed);
    if(result.ec!=std::errc{
    }
    || result.ptr!=seedText.data()+seedText.size()) return 2;
    try {
        std::cout<<greekText(readAsciiFile(file),seed);
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string greekText(const std::string& text, std::uint32_t seed) {
    /* BEGIN 1：greekText */
    // 提示：先读入整个文件，遇到字母时用种子驱动的随机数换成同大小写的另一个字母，非字母原样输出。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
