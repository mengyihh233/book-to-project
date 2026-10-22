#include "lesson.h"
#include <cassert>
int main(){
assert(defaultExtension("a.b/c",".txt")=="a.b/c.txt");assert(defaultExtension("x.h","*.cpp")=="x.cpp");assert(defaultExtension("x.h","*")=="x");
}
