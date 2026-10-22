#pragma once
#include "../../../../教学辅助/vector_lesson.h"
#include <stack>
#include <queue>
inline void reverseQueue(std::queue<std::string>& values) {
    std::stack<std::string> temporary;
    while(!values.empty()){temporary.push(values.front());values.pop();}
    while(!temporary.empty()){values.push(temporary.top());temporary.pop();}
}
