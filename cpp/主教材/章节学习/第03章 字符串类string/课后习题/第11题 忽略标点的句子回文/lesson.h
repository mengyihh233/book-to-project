#pragma once
#include <string>
#include <stdexcept>
inline bool sentenceLetter(char c) { return (c>='a' && c<='z') || (c>='A' && c<='Z'); }
inline char sentenceLower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline bool isSentencePalindrome(const std::string& str) {
    std::size_t left=0,right=str.size();
    while(left<right) {
        while(left<right && !sentenceLetter(str[left])) ++left;
        while(left<right && !sentenceLetter(str[right-1])) --right;
        if(left<right) {
            if(sentenceLower(str[left])!=sentenceLower(str[right-1])) return false;
            ++left; --right;
        }
    }
    return true;
}
