#include "lesson.h"
int main() {
    std::string file,seedText,extra;
    if(!book_input::logicalLine(std::cin,file)||!book_input::logicalLine(std::cin,seedText)||book_input::logicalLine(std::cin,extra)) return 2;
    std::uint32_t seed=0;
    auto result=std::from_chars(seedText.data(),seedText.data()+seedText.size(),seed);
    if(result.ec!=std::errc{} || result.ptr!=seedText.data()+seedText.size()) return 2;
    try {std::cout<<greekText(readAsciiFile(file),seed);}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
