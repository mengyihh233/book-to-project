#include "lesson.h"
int main(){try {const auto r=simulateChain(std::cin);printChain(r,std::cout);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
