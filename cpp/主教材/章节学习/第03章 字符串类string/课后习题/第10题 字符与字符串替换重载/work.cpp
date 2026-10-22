// 【本题说明开始】
// 第3章习题10：字符与字符串替换重载
//
// 题目：输入四行：模式char或string、原字符串、搜索内容、替换内容。char模式后两行必须各有一个字符。string模式按原字符串从左到右、互不重叠地替换，不再次扫描新插入内容；允许替换为空。空搜索串拒绝，输出超过1000000字节拒绝。上…
// 实现什么：replaceAll(std::string str, char from, char to)、replaceAll(const std::string& str, const std::string& from, const std::string& to)
// 写在哪里：只补下方 BEGIN 1、BEGIN 2 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <stdexcept>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline void appendChecked(std::string& out,const std::string& chunk) {
    constexpr std::size_t limit=1000000;
    if(chunk.size()>limit-out.size()) throw std::length_error("replacement output limit exceeded");
    out+=chunk;
}

// 本题要实现的接口（声明已给出）。
std::string replaceAll(std::string str, char from, char to);
std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto mode=line(),s=line(),from=line(),to=line();
        endInput();
        if(mode=="char") {
            if(from.size()!=1 || to.size()!=1) throw std::invalid_argument("char mode requires two single characters");
            std::cout<<replaceAll(s,from[0],to[0])<<"\n";
        } else if(mode=="string") std::cout<<replaceAll(s,from,to)<<"\n";
        else throw std::invalid_argument("expected char or string mode");
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 2 个函数体。

std::string replaceAll(std::string str, char from, char to) {
    /* BEGIN 1：replaceAll */
    // 提示：char 版：逐字符扫描，等于 from 的换成 to，返回新串。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
    /* BEGIN 2：replaceAll */
    // 提示：string 版：从左到右找 from，拼上中间段与 to，再跳过 from 继续；from 为空要拒绝。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}
