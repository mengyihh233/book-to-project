#include "lesson.h"
int main(){try{
    std::string line,extra;if(!book_input::logicalLine(std::cin,line)||line.size()>100000)throw std::invalid_argument("missing or large string");
    if(book_input::logicalLine(std::cin,extra)||std::cin.bad())throw std::invalid_argument("extra input");
    std::cout<<(bracketsMatch(line)?"true":"false")<<'\n';
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
