#pragma once
#include <string>
#include <stdexcept>
inline std::string removeDoubledLetters(const std::string& str) {
    std::string result;
    for(char c : str) if(result.empty() || result.back()!=c) result+=c;
    return result;
}
