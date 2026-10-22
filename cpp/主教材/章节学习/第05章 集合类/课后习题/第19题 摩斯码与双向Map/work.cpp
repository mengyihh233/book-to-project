// 【本题说明开始】
// 第5章习题19：摩斯码与双向Map
//
// 题目：按每行首字符决定翻译方向：ASCII字母开头编码，点或连字符开头解码，空行结束；EOF也正常结束。不提前去掉首字符前的空格。只处理原书26个字母，忽略其他字符，编码统一大写、码之间一个
//   空格；解码按空格/制表符分隔，输出连续大写字母。其他字符被忽略，不创造新分隔；空行后内容不再处理。
// 实现什么：std::vector<std::string> translateMorseSession(std::istream& in)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "morse_table.h"
#include "../../../../教学辅助/input_line.h"
#include <istream>
#include <stdexcept>
#include <vector>
#include <iostream>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline bool asciiLetter(char c){return (c>='A'&&c<='Z')||(c>='a'&&c<='z');}
inline char asciiUpper(char c){return c>='a'&&c<='z'?static_cast<char>(c-'a'+'A'):c;}
inline void checkMorseLength(const std::string& line){
    if(line.size()>10000)throw std::length_error("line exceeds 10000 bytes");
}
inline std::string encodeMorse(const std::string& line){
    checkMorseLength(line);
    std::string out;
    for(char c:line){
        if(!asciiLetter(c))continue;
        if(!out.empty())out+=' ';
        out+=morseAlphabet().at(asciiUpper(c));
    }
    return out;
}
inline std::string decodeMorse(const std::string& line){
    checkMorseLength(line);
    static const auto reverse=[](){
        std::map<std::string,char> result;
        for(const auto& item:morseAlphabet())result.emplace(item.second,item.first);
        return result;
    }();
    std::string out,token;
    const auto flush=[&](){
        if(token.empty())return;
        const auto it=reverse.find(token);
        if(it==reverse.end())throw std::invalid_argument("unknown Morse letter");
        out+=it->second;token.clear();
    };
    for(char c:line){
        if(c=='.'||c=='-')token+=c;
        else if(c==' '||c=='\t')flush();
        // 除空格/制表符外，其他字符忽略；它们不创造字母间隔。
    }
    flush();return out;
}

// 本题要实现的接口（声明已给出）。
std::vector<std::string> translateMorseSession(std::istream& in);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try{
        const auto translated=translateMorseSession(std::cin);
        for(const auto& line:translated)std::cout<<line<<'\n';
    } catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::vector<std::string> translateMorseSession(std::istream& in) {
    /* BEGIN 1：translateMorseSession */
    // 提示：先看每行首字符判断方向，再按字母或空格切分；编码和解码共用同一张正反表。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
