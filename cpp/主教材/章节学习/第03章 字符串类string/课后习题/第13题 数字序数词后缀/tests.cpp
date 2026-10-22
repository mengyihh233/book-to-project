#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { for(long long n=0;n<=999;++n) { const auto text=createOrdinalForm(n); assert(text.find(std::to_string(n))==0); if(n%100>=11 && n%100<=13) assert(text==std::to_string(n)+"th"); } assert(createOrdinalForm(121)=="121st"); assert(createOrdinalForm(9223372036854775807LL)=="9223372036854775807th"); bool bad=false; try { createOrdinalForm(-1); } catch(const std::invalid_argument&) { bad=true; } assert(bad); std::cout<<"contracts passed\n"; }
