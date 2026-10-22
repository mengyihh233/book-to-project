#include "lesson.h"
int main(){try{
    std::string text,line,extra;if(!book_input::logicalLine(std::cin,text)||text.size()>10000)throw std::invalid_argument("missing or large stack");
    for(unsigned char c:text)if(c<32||c>126)throw std::invalid_argument("ASCII stack required");
    if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing roll parameters");
    std::istringstream parameters(line);int n;long long k;
    if(!(parameters>>n>>k))throw std::invalid_argument("invalid roll parameters");
    parameters>>std::ws;if(!parameters.eof()||book_input::logicalLine(std::cin,extra)||std::cin.bad())throw std::invalid_argument("extra input");
    std::stack<char> values;for(char c:text)values.push(c);roll(values,n,k);
    std::string result(values.size(),' ');for(std::size_t i=result.size();i>0;--i){result[i-1]=values.top();values.pop();}
    std::cout<<result<<'\n';
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
