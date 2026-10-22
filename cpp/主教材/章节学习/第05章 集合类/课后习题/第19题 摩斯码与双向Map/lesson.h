#pragma once
#include "morse_table.h"
#include "../../../../教学辅助/input_line.h"
#include <istream>
#include <stdexcept>
#include <vector>
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
inline std::vector<std::string> translateMorseSession(std::istream& in){
    std::vector<std::string> result;
    std::string line;std::size_t bytes=0;
    while(book_input::logicalLine(in,line)){
        if(line.empty())break;
        bytes+=line.size();
        if(result.size()>=1000||bytes>1024*1024)throw std::length_error("session limit exceeded");
        if(asciiLetter(line.front()))result.push_back(encodeMorse(line));
        else if(line.front()=='.'||line.front()=='-')result.push_back(decodeMorse(line));
        else throw std::invalid_argument("first character must be an ASCII letter, dot or dash");
    }
    return result;
}
