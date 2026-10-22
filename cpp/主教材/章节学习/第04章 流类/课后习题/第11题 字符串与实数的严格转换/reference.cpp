#include "lesson.h"
int main() {
    std::string text,extra;
    if(!book_input::logicalLine(std::cin,text)||book_input::logicalLine(std::cin,extra)) return 2;
    try {std::cout<<realToString(stringToReal(text))<<'\n';}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
