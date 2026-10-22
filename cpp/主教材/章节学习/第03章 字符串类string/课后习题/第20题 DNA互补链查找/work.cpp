// 【本题说明开始】
// 第3章习题20：DNA互补链查找
//
// 题目：输入三行：短链、长链、起始位置（0..1000000或DEFAULT）。短链逐位取互补后在长链中查找，返回第一个下标，未找到为-1。接受A/C/G/T大小写，拒绝其他字符；不反转短链。空短链按string::find规则匹配start位置…
// 实现什么：findDNAMatch(std::string shortDNA, std::string longDNA, int start=0)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <stdexcept>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline char lower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upper(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline bool letter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline bool vowel(char c) { return std::string("aeiou").find(lower(c))!=std::string::npos; }
inline char complement(char c) {
    switch(upper(c)) { case 'A':return 'T';case 'T':return 'A';case 'C':return 'G';case 'G':return 'C'; }
    throw std::invalid_argument("DNA alphabet must be A/C/G/T");
}

// 本题要实现的接口（声明已给出）。
int findDNAMatch(std::string shortDNA, std::string longDNA, int start=0);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto shortDNA=line(),longDNA=line(),position=line();
        endInput();
        std::cout<<(position=="DEFAULT" ? findDNAMatch(shortDNA,longDNA) : findDNAMatch(shortDNA,longDNA,static_cast<int>(indexValue(position))))<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

int findDNAMatch(std::string shortDNA, std::string longDNA, int start) {
    /* BEGIN 1：findDNAMatch */
    // 提示：在长链上从左往右逐位比较互补结果，返回第一个完全匹配的下标；找不到返回 -1。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
