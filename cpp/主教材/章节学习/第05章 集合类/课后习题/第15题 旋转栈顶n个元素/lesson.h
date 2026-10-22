#pragma once
#include "../../../../教学辅助/vector_lesson.h"
#include <stack>
#include <queue>
inline void roll(std::stack<char>& values,int n,long long k) {
    if(n<0 || k<0 || static_cast<std::size_t>(n)>values.size())throw std::out_of_range("roll: argument out of range");
    if(n==0)return;
    int shift=static_cast<int>(k%n);if(shift==0)return;
    std::vector<char> top;top.reserve(static_cast<std::size_t>(n));
    for(int i=0;i<n;++i){top.push_back(values.top());values.pop();}
    std::rotate(top.begin(),top.begin()+shift,top.end());
    for(auto it=top.rbegin();it!=top.rend();++it)values.push(*it);
}
