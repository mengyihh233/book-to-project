#include "lesson.h"
int main() {
    std::string name,extra;
    if(!book_input::logicalLine(std::cin,name) || book_input::logicalLine(std::cin,extra)) return 2;
    std::cout<<getRoot(name)<<'\n'<<getExtension(name)<<'\n';
}
