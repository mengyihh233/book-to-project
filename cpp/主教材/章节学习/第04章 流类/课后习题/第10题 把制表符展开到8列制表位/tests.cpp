#include "lesson.h"
#include <cassert>
int main(){
assert(expandTabs("abc\tpqrst\txyz")=="abc     pqrst   xyz");assert(expandTabs("12345678\t")=="12345678        ");assert(expandTabs("\t\t")==std::string(16,' '));
}
