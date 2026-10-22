// 【本题说明开始】
// 第4章 · 习题6：补充或强制替换扩展名
//
// 题目：输入两行：文件名、扩展名。ext通常为.txt；已存在扩展名时保持原样，无扩展名才补充。ext前加*强制替换，单独*表示去除扩展名；空ext表示不追加。ext去掉可选*后必须为空或以点
//   开头，且不可含路径分隔符或*。路径解析沿用第5题，不操作真实文件。
// 实现什么：std::string defaultExtension(const std::string& name, std::string ext)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/input_line.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline std::string::size_type extensionPosition(const std::string& name) {
    auto slash=name.find_last_of("/\\");
    auto dot=name.find_last_of('.');
    return dot!=std::string::npos && (slash==std::string::npos || dot>slash) ? dot : std::string::npos;
}
inline std::string getRoot(const std::string& name) {
    auto pos=extensionPosition(name);
    return pos==std::string::npos ? name : name.substr(0,pos);
}
inline std::string getExtension(const std::string& name) {
    auto pos=extensionPosition(name);
    return pos==std::string::npos ? "" : name.substr(pos);
}

// 本题要实现的接口（声明已给出）。
std::string defaultExtension(const std::string& name, std::string ext);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string name,ext,extra;
    if(!book_input::logicalLine(std::cin,name)||!book_input::logicalLine(std::cin,ext)||book_input::logicalLine(std::cin,extra)) return 2;
    try {
        std::cout<<defaultExtension(name,ext)<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string defaultExtension(const std::string& name, std::string ext) {
    /* BEGIN 1：defaultExtension */
    // 提示：先看 ext：以 * 开头表示强制替换，单独一个 * 表示去掉扩展名，空串表示不追加；否则只在没有扩展名时接在末尾。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
