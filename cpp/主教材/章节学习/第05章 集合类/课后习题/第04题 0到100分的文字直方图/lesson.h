#pragma once
#include "../../../../教学辅助/vector_lesson.h"
inline std::array<std::size_t,11> histogram(const std::vector<int>& scores) {
    std::array<std::size_t,11> counts{};
    for(int score:scores) {
        if(score<0 || score>100) throw std::out_of_range("score outside 0..100");
        ++counts[static_cast<std::size_t>(score/10)];
    }
    return counts;
}
