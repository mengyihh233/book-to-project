#include "lesson.h"
int main() {
    try {const auto trace=readQueueTrace(std::cin);printQueueResult(simulateSeparate(trace),trace.services.size(),std::cout);}
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}
}
