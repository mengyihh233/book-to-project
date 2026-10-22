#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { const std::string s="bOOLean"; assert(capitalize(s)=="Boolean" && s=="bOOLean"); assert(capitalize("").empty()); assert(capitalize("42ABC")=="42abc"); std::cout<<"contracts passed\n"; }
