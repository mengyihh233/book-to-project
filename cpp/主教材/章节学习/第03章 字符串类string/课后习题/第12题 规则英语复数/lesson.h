#pragma once
#include <string>
#include <stdexcept>
inline std::string createRegularPlural(const std::string& word) {
    if(word.empty()) throw std::invalid_argument("word must be nonempty lowercase ASCII letters");
    for(char c : word) if(c<'a' || c>'z') throw std::invalid_argument("expected lowercase ASCII word");
    const auto size=word.size();
    const char last=word.back();
    const std::string tail=size>=2 ? word.substr(size-2) : "";
    if(last=='s' || last=='x' || last=='z' || tail=="ch" || tail=="sh") return word+"es";
    if(size>=2 && last=='y' && std::string("aeiou").find(word[size-2])==std::string::npos)
        return word.substr(0,size-1)+"ies";
    return word+"s";
}
