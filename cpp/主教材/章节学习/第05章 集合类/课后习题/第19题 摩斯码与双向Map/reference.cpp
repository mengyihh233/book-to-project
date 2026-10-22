#include "lesson.h"
#include <iostream>
int main(){
    try{const auto translated=translateMorseSession(std::cin);for(const auto& line:translated)std::cout<<line<<'\n';}
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}
}
