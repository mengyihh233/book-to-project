#pragma once
#include <string>
#include <stdexcept>
inline char lower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upper(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline bool letter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline bool vowel(char c) { return std::string("aeiou").find(lower(c))!=std::string::npos; }
inline std::string obenglobish(const std::string& word) {
    if(word.empty()) throw std::invalid_argument("word must be nonempty");
    for(char c : word) if(c<'a' || c>'z') throw std::invalid_argument("expected lowercase ASCII word");
    std::string result;
    for(std::size_t i=0;i<word.size();++i) {
        const bool afterVowel=i>0 && vowel(word[i-1]);
        const bool finalE=i+1==word.size() && word[i]=='e';
        if(vowel(word[i]) && !afterVowel && !finalE) result+="ob";
        result+=word[i];
    }
    return result;
}
