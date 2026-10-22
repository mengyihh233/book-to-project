#include "lesson.h"
int main(){try{
    std::string line;if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing count");
    int n=strictNumber<int>(line);if(n<0||n>10000)throw std::out_of_range("count");
    std::queue<std::string> values;
    for(int i=0;i<n;++i){if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing string");values.push(line);}
    if(book_input::logicalLine(std::cin,line)||std::cin.bad())throw std::invalid_argument("extra input");
    reverseQueue(values);std::cout<<n<<'\n';while(!values.empty()){std::cout<<values.front()<<'\n';values.pop();}
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
