#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline bool asciiSpace(char c) { return c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\v' || c=='\f'; }
inline std::string trim(const std::string& str) {
    std::size_t first=0,last=str.size();
    while (first<last && asciiSpace(str[first])) ++first;
    while (last>first && asciiSpace(str[last-1])) --last;
    return str.substr(first,last-first);
}
