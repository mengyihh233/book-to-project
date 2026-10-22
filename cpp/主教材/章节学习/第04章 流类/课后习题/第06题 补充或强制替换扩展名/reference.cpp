#include "lesson.h"
int main() {
    std::string name,ext,extra;
    if(!book_input::logicalLine(std::cin,name)||!book_input::logicalLine(std::cin,ext)||book_input::logicalLine(std::cin,extra)) return 2;
    try {std::cout<<defaultExtension(name,ext)<<'\n';}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
