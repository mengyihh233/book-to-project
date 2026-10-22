#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(removeDoubledLetters("bookkeeper")=="bokeper"); assert(removeDoubledLetters("committee")=="comite"); assert(removeDoubledLetters("AAAA")=="A"); assert(removeDoubledLetters("ababa")=="ababa"); assert(removeDoubledLetters("").empty()); std::cout<<"contracts passed\n"; }
