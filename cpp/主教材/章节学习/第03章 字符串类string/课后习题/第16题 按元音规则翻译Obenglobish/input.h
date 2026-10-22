#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <charconv>
inline std::string line() {
    std::string result;
    if (!std::getline(std::cin,result)) throw std::invalid_argument("missing line (empty line is valid)");
    if (result.size()>10000) throw std::out_of_range("line too long");
    for (unsigned char c : result) if (c>127) throw std::invalid_argument("this exercise uses ASCII input");
    return result;
}
inline void endInput() { std::string extra; if (std::getline(std::cin,extra)) throw std::invalid_argument("unexpected extra line"); }
inline std::size_t indexValue(const std::string& text) {
    unsigned long long value=0;
    const auto result=std::from_chars(text.data(),text.data()+text.size(),value);
    if (result.ec!=std::errc{} || result.ptr!=text.data()+text.size() || value>1000000)
        throw std::invalid_argument("index/count must be an integer in 0..1000000");
    return static_cast<std::size_t>(value);
}
