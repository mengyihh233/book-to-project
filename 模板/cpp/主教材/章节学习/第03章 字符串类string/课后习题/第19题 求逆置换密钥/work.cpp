// 【本题说明开始】
// 第3章习题19：求逆置换密钥
//
// 题目：输入一行26字母置换密钥，输出能解码其结果的逆密钥，规范为大写。拒绝重复字母、非字母、长度不符；不通过简单倒序代替求逆。
// 实现什么：invertKey(const std::string& rawKey)
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
inline std::string normalizedKey(std::string key) {
    if(key.size()!=26) throw std::invalid_argument("key must contain exactly 26 letters");
    bool seen[26]={};
    for(char& c : key) {
        c=upper(c);
        if(c<'A' || c>'Z' || seen[c-'A']) throw std::invalid_argument("key must be a permutation of A..Z");
        seen[c-'A']=true;
    }
    return key;
}

// 本题要实现的接口（声明已给出）。
std::string invertKey(const std::string& rawKey);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto key=line();
        endInput();
        std::cout<<invertKey(key)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string invertKey(const std::string& rawKey) {
    /* BEGIN 1：invertKey */
    // 提示：先规范密钥，再反过来填：逆密钥的第 i 位，是原密钥里字母表中第 i 个字母所在的位置。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
