#include "lesson.h"
int main() {
    std::string type,line,extra;
    if(!book_input::logicalLine(std::cin,type)||!book_input::logicalLine(std::cin,line)) return 2;
    try {
        int calls=strictNumber<int>(line);
        if(calls<1 || calls>20) throw std::out_of_range("calls must be 1..20");
        std::ostringstream out;out.imbue(std::locale::classic());
        if(type=="int") displayBlocks<int>(std::cin,out,calls);
        else if(type=="double") displayBlocks<double>(std::cin,out,calls);
        else if(type=="string") displayBlocks<std::string>(std::cin,out,calls);
        else throw std::invalid_argument("unknown type");
        if(book_input::logicalLine(std::cin,extra)) throw std::invalid_argument("extra input after blocks");
        std::cout<<out.str();
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
