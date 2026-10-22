#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { std::string s="banana"; removeCharactersInPlace(s,"an"); assert(s=="b"); s="abc"; removeCharactersInPlace(s,s); assert(s.empty()); s="  abc  "; removeCharactersInPlace(s,""); assert(s=="  abc  "); s="aaaaab"; removeCharactersInPlace(s,"a"); assert(s=="b"); std::cout<<"contracts passed\n"; }
