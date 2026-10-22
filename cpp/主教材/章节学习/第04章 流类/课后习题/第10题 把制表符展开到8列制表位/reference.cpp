#include "lesson.h"
int main() {
    std::string input,output,extra;
    if(!book_input::logicalLine(std::cin,input)||!book_input::logicalLine(std::cin,output)||book_input::logicalLine(std::cin,extra)) return 2;
    try {auto text=expandTabs(readAsciiFile(input));writeNewFile(output,text);}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
