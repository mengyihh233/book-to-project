#include "lesson.h"
int main() {
    try {
        double number=getReal("Real: ");
        std::string label=getLine("Label: ");
        std::cout<<realToString(number)<<'\n'<<label<<'\n';
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
