#include "lesson.h"
int main() {
    try {auto grid=readGrid(std::cin);std::cout<<(isMagicSquare(grid)?"true":"false")<<'\n';}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
