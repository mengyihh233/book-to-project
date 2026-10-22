#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { const std::string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; assert(encodeSubstitution(alphabet,"QWERTYUIOPASDFGHJKLZXCVBNM")=="QWERTYUIOPASDFGHJKLZXCVBNM"); bool bad=false; try { encodeSubstitution("a",std::string(26,'A')); } catch(const std::invalid_argument&) { bad=true; } assert(bad); std::cout<<"contracts passed\n"; }
