#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { for(std::size_t len=0;len<=30;++len) { std::string s(len,'x'); for(std::size_t pos=0;pos<=len;++pos) { assert(substr(s,pos)==s.substr(pos)); for(std::size_t n=0;n<=len+2;++n) assert(substr(s,pos,n)==s.substr(pos,n)); assert(substr(s,pos,std::string::npos)==s.substr(pos)); } } bool rejected=false; try { substr("x",2); } catch(const std::out_of_range&) { rejected=true; } assert(rejected); std::cout<<"contracts passed\n"; }
