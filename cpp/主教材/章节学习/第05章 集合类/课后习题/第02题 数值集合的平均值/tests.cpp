#include "lesson.h"
#include <cassert>
int main(){
assert(mean({1,2,3,4})==2.5);bool error=false;try{mean({});}catch(const std::exception&){error=true;}assert(error);
}
