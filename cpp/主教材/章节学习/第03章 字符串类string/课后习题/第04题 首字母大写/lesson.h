#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline char lowerAscii(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upperAscii(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline std::string capitalize(std::string str) {
    for (char& c : str) c=lowerAscii(c);
    if (!str.empty()) str[0]=upperAscii(str[0]);
    return str;
}
