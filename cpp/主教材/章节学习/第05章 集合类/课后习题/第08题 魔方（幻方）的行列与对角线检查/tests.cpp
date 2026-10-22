#include "lesson.h"
#include <cassert>
int main(){
IntGrid zero(3,3);assert(isMagicSquare(zero));IntGrid rectangle(2,3);assert(!isMagicSquare(rectangle));IntGrid empty(0,0);assert(!isMagicSquare(empty));
}
