#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { assert(lineToPigLatin("This is Pig Latin.")=="Isthay isway Igpay Atinlay."); assert(wordToPigLatin("Rhythm")=="Rhythm"); assert(wordToPigLatin("Apple")=="Appleway"); assert(lineToPigLatin("").empty()); std::cout<<"contracts passed\n"; }
