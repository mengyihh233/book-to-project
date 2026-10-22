#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(createRegularPlural("baby")=="babies"); assert(createRegularPlural("boy")=="boys"); assert(createRegularPlural("quiz")=="quizes"); assert(createRegularPlural("brush")=="brushes"); bool bad=false; try { createRegularPlural(""); } catch(const std::invalid_argument&) { bad=true; } assert(bad); std::cout<<"contracts passed\n"; }
