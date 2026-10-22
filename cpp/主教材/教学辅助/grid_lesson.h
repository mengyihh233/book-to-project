#pragma once
#include "vector_lesson.h"
#include <utility>
// 本区的受限教学类型，不冒充Stanford Grid完整API。
class IntGrid {
    int rows_,cols_;std::vector<int> cells_;
public:
    IntGrid(int rows,int cols):rows_(rows),cols_(cols) {
        if(rows<0||cols<0||rows>100||cols>100) throw std::out_of_range("grid dimensions 0..100");
        cells_.resize(static_cast<std::size_t>(rows)*cols);
    }
    int rows() const {return rows_;}
    int cols() const {return cols_;}
    int& at(int row,int col) {
        if(row<0||row>=rows_||col<0||col>=cols_) throw std::out_of_range("grid index");
        return cells_.at(static_cast<std::size_t>(row)*cols_+col);
    }
    int at(int row,int col) const {
        if(row<0||row>=rows_||col<0||col>=cols_) throw std::out_of_range("grid index");
        return cells_.at(static_cast<std::size_t>(row)*cols_+col);
    }
};
inline IntGrid readGridShape(std::istream& input) {
    std::string line;
    if(!book_input::logicalLine(input,line)) throw std::invalid_argument("missing dimensions");
    std::istringstream in(line);int rows,cols;
    if(!(in>>rows>>cols)) throw std::invalid_argument("two dimensions required");
    in>>std::ws;if(!in.eof()) throw std::invalid_argument("extra dimensions");
    return IntGrid(rows,cols);
}
inline IntGrid readGrid(std::istream& input) {
    IntGrid grid=readGridShape(input);std::string line;
    if(grid.cols()!=0) for(int row=0;row<grid.rows();++row) {
        if(!book_input::logicalLine(input,line)) throw std::invalid_argument("missing grid row");
        std::istringstream in(line);
        for(int col=0;col<grid.cols();++col) if(!(in>>grid.at(row,col))) throw std::invalid_argument("invalid grid cell");
        in>>std::ws;if(!in.eof()) throw std::invalid_argument("extra grid cell");
    }
    if(book_input::logicalLine(input,line)||input.bad()) throw std::invalid_argument("extra grid input");
    return grid;
}
