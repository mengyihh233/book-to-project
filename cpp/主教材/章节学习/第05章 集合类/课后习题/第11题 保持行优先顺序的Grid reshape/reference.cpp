#include "lesson.h"
inline void printGrid(const IntGrid& grid,std::ostream& out) {
    out<<grid.rows()<<' '<<grid.cols()<<'\n';
    if(grid.cols()) for(int r=0;r<grid.rows();++r) {
        for(int c=0;c<grid.cols();++c) out<<(c?" ":"")<<grid.at(r,c);
        out<<'\n';
    }
}
int main() {
    try {
        auto grid=readGridShape(std::cin);std::string line;
        if(grid.cols()) for(int r=0;r<grid.rows();++r) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing row");
            std::istringstream row(line);
            for(int c=0;c<grid.cols();++c) if(!(row>>grid.at(r,c))) throw std::invalid_argument("invalid cell");
            row>>std::ws;if(!row.eof()) throw std::invalid_argument("extra cell");
        }
        auto shape=readGridShape(std::cin);
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra input");
        reshape(grid,shape.rows(),shape.cols());printGrid(grid,std::cout);
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
