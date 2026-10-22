#include "lesson.h"
int main() {
    std::string input,output,letters,extra;
    if(!book_input::logicalLine(std::cin,input)||!book_input::logicalLine(std::cin,output)||!book_input::logicalLine(std::cin,letters)||book_input::logicalLine(std::cin,extra)) return 2;
    try {auto text=banishLetters(readAsciiFile(input),letters);writeNewFile(output,text);}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
