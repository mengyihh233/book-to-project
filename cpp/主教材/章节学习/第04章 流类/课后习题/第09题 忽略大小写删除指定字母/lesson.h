#include "../../../../教学辅助/input_line.h"
#pragma once
#include "../../../../教学辅助/file_lesson.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cstdint>
#include <charconv>
#include <array>
inline std::string banishLetters(const std::string& text,const std::string& letters) {
    std::array<bool,26> banned{};
    for(unsigned char c:letters) {
        if(c>='A' && c<='Z') c=static_cast<unsigned char>(c-'A'+'a');
        if(c<'a' || c>'z') throw std::invalid_argument("letters must be ASCII alphabetic");
        banned[c-'a']=true;
    }
    std::string output;
    for(unsigned char c:text) {
        auto lower=c>='A' && c<='Z' ? c-'A'+'a' : c;
        if(lower<'a' || lower>'z' || !banned[lower-'a']) output+=static_cast<char>(c);
    }
    return output;
}
