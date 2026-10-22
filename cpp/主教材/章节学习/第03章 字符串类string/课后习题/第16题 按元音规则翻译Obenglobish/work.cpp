// 【本题说明开始】
// 第3章习题16：按元音规则翻译Obenglobish
//
// 题目：输入非空全小写ASCII单词。元音前加ob，但前一个原字符也是元音时不加，位于词尾的e也不加。判断依据始终是原单词，不是已生成结果；不猜测真实发音。
// 实现什么：obenglobish(const std::string& word)
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

// 本题要实现的接口（声明已给出）。
std::string obenglobish(const std::string& word);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto word=line();
        endInput();
        std::cout<<obenglobish(word)<<"\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string obenglobish(const std::string& word) {
    /* BEGIN 1：obenglobish */
    // 提示：遍历原词，在元音前插入 ob；但前一个原字符也是元音时不插，词尾的 e 也不插。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
