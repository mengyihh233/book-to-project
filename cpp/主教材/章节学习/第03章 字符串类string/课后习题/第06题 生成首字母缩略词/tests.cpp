#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(acronym("self-contained underwater breathing apparatus")=="SCUBA"); assert(acronym("...a--B / c!")=="ABC"); assert(acronym("").empty()); std::cout<<"contracts passed\n"; }
