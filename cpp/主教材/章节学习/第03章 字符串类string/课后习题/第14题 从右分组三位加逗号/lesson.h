#pragma once
#include <string>
#include <stdexcept>
inline std::string addCommas(const std::string& digits) {
    if(digits.empty()) throw std::invalid_argument("digits must be nonempty");
    for(char c : digits) if(c<'0' || c>'9') throw std::invalid_argument("digits only: no sign or decimal point");
    std::string result;
    for(std::size_t i=0;i<digits.size();++i) {
        if(i>0 && (digits.size()-i)%3==0) result+=',';
        result+=digits[i];
    }
    return result;
}
