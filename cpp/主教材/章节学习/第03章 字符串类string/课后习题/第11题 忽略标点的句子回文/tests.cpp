#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(isSentencePalindrome("Madam, I'm Adam.")); assert(isSentencePalindrome("1a2")); assert(isSentencePalindrome("")); assert(isSentencePalindrome("!!!")); assert(!isSentencePalindrome("abc")); assert(isSentencePalindrome("  Aa !!")); std::cout<<"contracts passed\n"; }
