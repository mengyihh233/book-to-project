#pragma once
#include <string>
#include <stdexcept>
inline char lower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upper(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline bool letter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline bool vowel(char c) { return std::string("aeiou").find(lower(c))!=std::string::npos; }
inline std::string encodeCaesarCipher(const std::string& text,long long shift) {
    const int normalized=static_cast<int>((shift%26+26)%26);
    std::string result=text;
    for(char& c : result) if(letter(c)) c=static_cast<char>('A'+(upper(c)-'A'+normalized)%26);
    return result;
}
