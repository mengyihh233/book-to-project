#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { std::string s="banana"; assert(removeCharacters(s,"an")=="b" && s=="banana"); assert(removeCharacters(s,s).empty()); assert(removeCharacters(s,"")==s); std::cout<<"contracts passed\n"; }
