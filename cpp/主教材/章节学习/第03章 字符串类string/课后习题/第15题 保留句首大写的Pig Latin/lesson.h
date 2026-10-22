#pragma once
#include <string>
#include <stdexcept>
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
inline std::string lineToPigLatin(const std::string& line) {
    std::string result;std::size_t pos=0;
    while(pos<line.size()) {
        if(!letter(line[pos])) { result+=line[pos++];continue; }
        const auto start=pos;while(pos<line.size() && letter(line[pos])) ++pos;
        result+=wordToPigLatin(line.substr(start,pos-start));
    }
    return result;
}
