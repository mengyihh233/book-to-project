#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline std::string substr(const std::string& str,std::size_t pos,std::size_t n=std::string::npos) {
    if (pos>str.size()) throw std::out_of_range("substring position exceeds size");
    const auto count=std::min(n,str.size()-pos);
    std::string result; result.reserve(count);
    for (std::size_t i=0;i<count;++i) result+=str[pos+i];
    return result;
}
