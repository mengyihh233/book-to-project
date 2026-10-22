#include "lesson.h"
int main() {
    try {
        std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int n=strictNumber<int>(line);
        if(n<0 || n>10000) throw std::out_of_range("record count");
        std::vector<int> data;
        for(int i=0;i<n;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing score");
            data.push_back(strictNumber<int>(line));
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra data");
        auto counts=histogram(data);std::ostringstream out;
        for(int i=0;i<11;++i) out<<std::setw(4)<<(i==10?"100":std::to_string(i*10)+"s")<<": "<<std::string(counts[i],'*')<<'\n';
        std::cout<<out.str();
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
