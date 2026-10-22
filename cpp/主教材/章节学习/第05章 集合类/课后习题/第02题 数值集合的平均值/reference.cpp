#include "lesson.h"
int main() {
    try {auto data=numberRecords(std::cin);std::cout<<std::setprecision(17)<<mean(data)<<'\n';}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
