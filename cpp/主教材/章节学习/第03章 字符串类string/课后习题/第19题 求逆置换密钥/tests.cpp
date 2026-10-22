#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { const std::string key="QWERTYUIOPASDFGHJKLZXCVBNM"; assert(invertKey(invertKey(key))==key); assert(invertKey("abcdefghijklmnopqrstuvwxyz")=="ABCDEFGHIJKLMNOPQRSTUVWXYZ"); std::cout<<"contracts passed\n"; }
