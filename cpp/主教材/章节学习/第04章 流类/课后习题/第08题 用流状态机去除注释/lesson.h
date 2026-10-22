#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>
inline void removeComments(std::istream& in,std::ostream& out) {
    char c;
    while(in.get(c)) {
        if(c!='/' || (in.peek()!='/' && in.peek()!='*')) {out.put(c);continue;}
        char kind=static_cast<char>(in.get());
        if(kind=='/') {
            while(in.get(c) && c!='\n') {}
            if(in) out.put('\n');
        } else {
            bool star=false,closed=false;
            while(in.get(c)) {
                if(star && c=='/') {closed=true;break;}
                star=c=='*';
            }
            if(!closed) throw std::invalid_argument("unterminated block comment");
        }
    }
    if(in.bad() || !out) throw std::runtime_error("stream failure");
}
