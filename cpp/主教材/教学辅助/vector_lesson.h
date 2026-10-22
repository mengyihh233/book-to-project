#pragma once
#include "input_line.h"
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <cmath>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <array>
#include <algorithm>
template<class T> T strictNumber(const std::string& text) {
    std::istringstream in(text);in.imbue(std::locale::classic());T value;
    if(!(in>>value)) throw std::invalid_argument("invalid numeric record");
    in>>std::ws;
    if(!in.eof()) throw std::invalid_argument("extra numeric data");
    if constexpr(std::is_floating_point_v<T>) {
        if(!std::isfinite(value) || std::abs(value)>1e150) throw std::out_of_range("real magnitude");
    }
    return value;
}
inline std::vector<double> numberRecords(std::istream& in,bool allowEmpty=false) {
    std::string line;
    if(!book_input::logicalLine(in,line)) throw std::invalid_argument("missing count");
    int count=strictNumber<int>(line);
    if(count<(allowEmpty?0:1) || count>10000) throw std::out_of_range("record count");
    std::vector<double> data;
    for(int i=0;i<count;++i) {
        if(!book_input::logicalLine(in,line)) throw std::invalid_argument("missing record");
        data.push_back(strictNumber<double>(line));
    }
    if(book_input::logicalLine(in,line)) throw std::invalid_argument("extra record");
    if(in.bad()) throw std::runtime_error("read failure");
    return data;
}
inline void validateNumbers(const std::vector<double>& data) {
    if(data.empty() || data.size()>10000) throw std::invalid_argument("empty or large vector");
    for(double x:data) if(!std::isfinite(x)||std::abs(x)>1e150) throw std::out_of_range("real magnitude");
}
