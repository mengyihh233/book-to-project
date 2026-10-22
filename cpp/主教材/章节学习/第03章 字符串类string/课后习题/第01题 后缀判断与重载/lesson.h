#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline bool endsWith(const std::string& str,const std::string& suffix) {
    if (suffix.size()>str.size()) return false;
    return str.compare(str.size()-suffix.size(),suffix.size(),suffix)==0;
}
inline bool endsWith(const std::string& str,char suffix) {
    return !str.empty() && str.back()==suffix;
}
