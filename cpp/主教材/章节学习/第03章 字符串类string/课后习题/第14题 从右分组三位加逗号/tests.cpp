#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(addCommas("0000")=="0,000"); assert(addCommas("123456")=="123,456"); const auto large=addCommas(std::string(10000,'9')); assert(large.size()==13333); std::string plain; for(char c : large) if(c!=',') plain+=c; assert(plain==std::string(10000,'9')); std::cout<<"contracts passed\n"; }
