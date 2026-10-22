#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline std::string removeCharacters(const std::string& str,const std::string& remove) {
    std::string result; result.reserve(str.size());
    for (char c : str) if (remove.find(c)==std::string::npos) result+=c;
    return result;
}
