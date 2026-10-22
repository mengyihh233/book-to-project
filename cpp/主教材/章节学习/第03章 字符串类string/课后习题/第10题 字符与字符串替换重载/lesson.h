#pragma once
#include <string>
#include <stdexcept>
inline std::string replaceAll(std::string str,char from,char to) {
    for(char& c : str) if(c==from) c=to;
    return str;
}
inline void appendChecked(std::string& out,const std::string& chunk) {
    constexpr std::size_t limit=1000000;
    if(chunk.size()>limit-out.size()) throw std::length_error("replacement output limit exceeded");
    out+=chunk;
}
inline std::string replaceAll(const std::string& str,const std::string& from,const std::string& to) {
    if(from.empty()) throw std::invalid_argument("search string must not be empty");
    std::string result; std::size_t cursor=0;
    while(true) {
        const auto found=str.find(from,cursor);
        if(found==std::string::npos) { appendChecked(result,str.substr(cursor)); break; }
        appendChecked(result,str.substr(cursor,found-cursor)); appendChecked(result,to);
        cursor=found+from.size();
    }
    return result;
}
