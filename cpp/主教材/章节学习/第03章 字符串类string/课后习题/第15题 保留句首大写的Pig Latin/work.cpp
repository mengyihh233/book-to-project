// 【本题说明开始】
// 第3章习题15：保留句首大写的Pig Latin
//
// 题目：输入整行英文文本，按连续ASCII字母段翻译，原样保留非字母。无元音的词不变；元音开头加way；否则把元音前的辅音段移到末尾加ay。含元音的词先规范成小写，原词首字母大写时再把译词首字母大写；全大写/混合大小写不额外保留。元音只含a/e/i…
// 实现什么：lineToPigLatin(const std::string& line)
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
inline std::string wordToPigLatin(std::string word) {
    if(word.empty()) return word;
    for(char c : word) if(!letter(c)) throw std::invalid_argument("word letters only");
    const bool capital=word.front()>='A' && word.front()<='Z';
    std::size_t first=0;while(first<word.size() && !vowel(word[first])) ++first;
    if(first==word.size()) return word;
    for(char& c : word) c=lower(c);
    std::string result=first==0 ? word+"way" : word.substr(first)+word.substr(0,first)+"ay";
    if(capital) result[0]=upper(result[0]);
    return result;
}

// 本题要实现的接口（声明已给出）。
std::string lineToPigLatin(const std::string& line);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto text=line();
        endInput();
        std::cout<<lineToPigLatin(text)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string lineToPigLatin(const std::string& line) {
    /* BEGIN 1：lineToPigLatin */
    // 提示：按连续字母段处理：无元音的词不变，元音开头加 way，否则把元音前的辅音段搬到末尾再加 ay。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
