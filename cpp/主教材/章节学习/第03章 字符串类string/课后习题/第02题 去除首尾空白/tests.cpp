#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(trim(" \t\n\r\v\f").empty()); assert(trim("\t a b \n")=="a b"); const std::string s="  x  "; assert(trim(s)=="x" && s=="  x  "); std::cout<<"contracts passed\n"; }
