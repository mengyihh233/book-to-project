#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(encodeCaesarCipher("IBM 9000",-1)=="HAL 9000"); assert(encodeCaesarCipher("az",26)=="AZ"); for(long long n : {0LL,1LL,-1LL,9223372036854775807LL,(-9223372036854775807LL-1)}) { const auto encoded=encodeCaesarCipher("Az-019",n); const auto inverse=(26-(n%26+26)%26)%26; assert(encodeCaesarCipher(encoded,inverse)=="AZ-019"); } std::cout<<"contracts passed\n"; }
