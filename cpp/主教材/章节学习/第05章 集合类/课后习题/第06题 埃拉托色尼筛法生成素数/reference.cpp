#include "lesson.h"
int main() {
    std::string line,extra;
    try {
        if(!book_input::logicalLine(std::cin,line)||book_input::logicalLine(std::cin,extra)) throw std::invalid_argument("one limit line required");
        auto values=primesUpTo(strictNumber<int>(line));
        for(std::size_t i=0;i<values.size();++i) std::cout<<(i?" ":"")<<values[i];
        std::cout<<'\n';
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
