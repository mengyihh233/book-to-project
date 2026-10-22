#include "lesson.h"
#include <cassert>
int main(){
auto p=primesUpTo(1000);assert(p.size()==168&&p.back()==997);assert(primesUpTo(1).empty());assert((primesUpTo(2)==std::vector<int>{2}));
}
