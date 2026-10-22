#pragma once
#include <string>
#include <stdexcept>
inline std::string createOrdinalForm(long long n) {
    if(n<0) throw std::invalid_argument("ordinal must be nonnegative");
    const auto lastTwo=n%100; std::string suffix="th";
    if(lastTwo<11 || lastTwo>13) {
        if(n%10==1) suffix="st";
        else if(n%10==2) suffix="nd";
        else if(n%10==3) suffix="rd";
    }
    return std::to_string(n)+suffix;
}
