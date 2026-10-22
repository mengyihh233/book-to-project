#include "../../../../教学辅助/input_line.h"
#pragma once
#include "../../../../教学辅助/file_lesson.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cstdint>
#include <charconv>
#include <array>
inline std::string expandTabs(const std::string& text) {
    std::string output;unsigned int column=0;
    for(char c:text) {
        if(c=='\t') {
            unsigned int spaces=8-column;
            output.append(spaces,' ');column=0;
        } else {
            output+=c;
            if(c=='\n' || c=='\r') column=0;
            else column=(column+1)%8;
        }
    }
    return output;
}
