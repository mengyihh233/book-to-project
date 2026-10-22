#pragma once
#include <string>
#include <stdexcept>
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
inline std::string invertKey(const std::string& rawKey) {
    const auto key=normalizedKey(rawKey);std::string result(26,'?');
    for(std::size_t i=0;i<26;++i) result[key[i]-'A']=static_cast<char>('A'+i);
    return result;
}
