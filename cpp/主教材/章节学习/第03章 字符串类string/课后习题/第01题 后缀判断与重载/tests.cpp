#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(endsWith("", "")); assert(!endsWith("", 'x')); assert(endsWith("abc",'c')); assert(!endsWith("abc",'b')); assert(endsWith("abc",std::string("bc"))); assert(!endsWith("abc","abcd")); std::cout<<"contracts passed\n"; }
