#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(scrabbleScore("ABCDEFGHIJKLMNOPQRSTUVWXYZ")==87); assert(scrabbleScore("abcdefghijklmnopqrstuvwxyz")==87); assert(scrabbleScore("FARM")==9); assert(scrabbleScore("? 123")==0); std::cout<<"contracts passed\n"; }
