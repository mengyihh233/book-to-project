#include "lesson.h"
#include <cassert>
int main(){
assert(getRoot("a.b/c")=="a.b/c");assert(getExtension(".x")==".x");assert(getRoot("")=="");
}
