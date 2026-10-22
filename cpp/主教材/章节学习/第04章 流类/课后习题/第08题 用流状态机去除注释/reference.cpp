#include "lesson.h"
int main() {
    std::ostringstream output;
    try {removeComments(std::cin,output);std::cout<<output.str();}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
