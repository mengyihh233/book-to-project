#pragma once
#include "../../../../教学辅助/vector_lesson.h"
#include <stack>
#include <queue>
inline bool bracketsMatch(const std::string& text) {
    std::stack<char> pending;
    for(char c:text) {
        if(c=='('||c=='['||c=='{')pending.push(c);
        else if(c==')'||c==']'||c=='}') {
            char expected=c==')'?'(':c==']'?'[':'{';
            if(pending.empty()||pending.top()!=expected)return false;
            pending.pop();
        }
    }
    return pending.empty();
}
