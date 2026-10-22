#include "lesson.h"
#include <cassert>
int main(){
std::istringstream in("1\n2\n\n3\n");std::vector<int> v{99};readVector(in,v);assert((v==std::vector<int>{1,2}));readVector(in,v);assert((v==std::vector<int>{3}));readVector(in,v);assert(v.empty());
}
