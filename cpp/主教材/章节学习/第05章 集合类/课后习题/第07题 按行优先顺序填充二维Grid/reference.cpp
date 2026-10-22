#include "lesson.h"
int main() {
    try {
        IntGrid grid=readGridShape(std::cin);std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int count=strictNumber<int>(line);
        if(count<0||count>10000) throw std::out_of_range("value count");
        std::vector<int> values;
        for(int i=0;i<count;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing value");
            values.push_back(strictNumber<int>(line));
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra input");
        fillGrid(grid,values);std::ostringstream out;
        out<<grid.rows()<<' '<<grid.cols()<<'\n';
        if(grid.cols()!=0) for(int row=0;row<grid.rows();++row) {
            for(int col=0;col<grid.cols();++col) out<<(col?" ":"")<<grid.at(row,col);
            out<<'\n';
        }
        std::cout<<out.str();
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
