#include "hist.h"
#include "../../../../教学辅助/vector_lesson.h"
int main() {
    try {
        std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing range");
        std::istringstream in(line);int low,high,width;
        if(!(in>>low>>high>>width)) throw std::invalid_argument("range requires 3 integers");
        in>>std::ws;if(!in.eof()) throw std::invalid_argument("extra range data");
        hist::Histogram chart(low,high,width);
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int count=strictNumber<int>(line);
        if(count<0||count>10000) throw std::out_of_range("record count");
        std::vector<int> data;
        for(int i=0;i<count;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing value");
            data.push_back(strictNumber<int>(line));
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra input");
        chart.addAll(data);std::cout<<chart.render();
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
