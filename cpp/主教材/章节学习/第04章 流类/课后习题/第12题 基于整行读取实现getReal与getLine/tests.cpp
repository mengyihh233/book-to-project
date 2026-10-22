#include "lesson.h"
#include <cassert>
int main(){
std::istringstream in("bad\n2.5\n  label  \n\n");auto* saved=std::cin.rdbuf(in.rdbuf());assert(getReal()==2.5);assert(getLine()=="  label  ");assert(getLine()=="");bool threw=false;try{getLine();}catch(const std::runtime_error&){threw=true;}assert(threw);std::cin.rdbuf(saved);std::cin.clear();
}
