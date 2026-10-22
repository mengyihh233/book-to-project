#include "../../../../教学辅助/input_line.h"
#pragma once
#include "../../../../教学辅助/file_lesson.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cstdint>
#include <charconv>
#include <array>
inline char randomLetter(std::mt19937& engine,bool upper) {
    // 拒绝法避免直接%26的余数偏差；mt19937输出为32位。
    std::uint32_t value;
    do {value=engine();} while(value>=4294967274U);
    return static_cast<char>((upper?'A':'a')+value%26);
}
inline std::string greekText(const std::string& text,std::uint32_t seed) {
    std::mt19937 engine(seed);std::string output;
    for(std::size_t i=0;i<text.size();++i) {
        unsigned char c=static_cast<unsigned char>(text[i]);
        if(c=='\r' && i+1<text.size() && text[i+1]=='\n') continue;
        if(c>='A' && c<='Z') output+=randomLetter(engine,true);
        else if(c>='a' && c<='z') output+=randomLetter(engine,false);
        else output+=static_cast<char>(c);
    }
    return output;
}
