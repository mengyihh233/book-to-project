#include "lesson.h"
#include <cassert>
int main(){
auto counts=histogram({0,9,10,99,100});assert(counts[0]==2&&counts[1]==1&&counts[9]==1&&counts[10]==1);bool error=false;try{histogram({101});}catch(const std::exception&){error=true;}assert(error);
}
