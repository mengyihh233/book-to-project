#pragma once
#include <istream>
#include <string>
namespace book_input {
inline bool logicalLine(std::istream& in,std::string& line) {
    if(!std::getline(in,line)) return false;
    if(!line.empty() && line.back()=='\r') line.pop_back();
    return true;
}
}
