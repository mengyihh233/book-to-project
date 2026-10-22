#include "lesson.h"
#include <cassert>
int main(){
for(double x:{0.0,-2.5,0.1,1e20,1e-20}) { assert(stringToReal(realToString(x))==x); }
bool threw=false;try{stringToReal("1x");}catch(const std::invalid_argument&){threw=true;}assert(threw);
}

