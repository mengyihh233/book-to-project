#include "lesson.h"
#include <cassert>
int main(){
assert(std::abs(stddev({1,2,3,4})-std::sqrt(1.25))<1e-12);assert(stddev({7})==0);assert(stddev({5,5,5})==0);
}
