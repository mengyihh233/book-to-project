#include "lesson.h"
#include <cassert>
int main(){
std::istringstream in("a/*x*/b//y\nc");std::ostringstream out;removeComments(in,out);assert(out.str()=="ab\nc");std::istringstream broken("/*");bool threw=false;try{removeComments(broken,out);}catch(const std::invalid_argument&){threw=true;}assert(threw);
}
