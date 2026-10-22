#pragma once
#include "../../../../教学辅助/vector_lesson.h"
#include <stack>
#include <queue>
inline void reverseIntegers(std::istream& in,std::ostream& out) {
    std::stack<int> values;std::string line;bool terminated=false;
    while(book_input::logicalLine(in,line)) {
        int x=strictNumber<int>(line);
        if(x==0){terminated=true;break;}
        if(values.size()==10000)throw std::out_of_range("too many records");
        values.push(x);
    }
    if(!terminated || book_input::logicalLine(in,line) || in.bad())throw std::invalid_argument("missing sentinel or extra input");
    while(!values.empty()){out<<values.top()<<'\n';values.pop();}
}
