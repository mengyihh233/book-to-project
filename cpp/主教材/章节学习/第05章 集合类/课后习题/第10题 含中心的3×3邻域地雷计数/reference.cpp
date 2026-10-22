#include "lesson.h"
inline void printGrid(const IntGrid& grid,std::ostream& out) {
    out<<grid.rows()<<' '<<grid.cols()<<'\n';
    if(grid.cols()) for(int r=0;r<grid.rows();++r) {
        for(int c=0;c<grid.cols();++c) out<<(c?" ":"")<<grid.at(r,c);
        out<<'\n';
    }
}
int main() {
    try {auto mines=readGrid(std::cin);IntGrid counts(0,0);fixCounts(mines,counts);printGrid(counts,std::cout);}
    catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
