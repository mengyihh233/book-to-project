#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(findDNAMatch("TGC","TAACGGTACGTC")==2); assert(findDNAMatch("TGC","TAACGGTACGTC",3)==7); assert(findDNAMatch("","ACGT",4)==4); assert(findDNAMatch("","ACGT",5)==-1); bool bad=false; try { findDNAMatch("AN","ACGT"); } catch(const std::invalid_argument&) { bad=true; } assert(bad); std::cout<<"contracts passed\n"; }
