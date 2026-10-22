#pragma once
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>
inline bool isMagicSquare(const IntGrid& grid) {
    if(grid.rows()==0||grid.rows()!=grid.cols()) return false;
    std::int64_t target=0;
    for(int col=0;col<grid.cols();++col) target+=grid.at(0,col);
    for(int row=0;row<grid.rows();++row) {
        std::int64_t rowSum=0,colSum=0;
        for(int col=0;col<grid.cols();++col) {rowSum+=grid.at(row,col);colSum+=grid.at(col,row);}
        if(rowSum!=target||colSum!=target) return false;
    }
    std::int64_t main=0,other=0;
    for(int i=0;i<grid.rows();++i) {main+=grid.at(i,i);other+=grid.at(i,grid.cols()-1-i);}
    return main==target&&other==target;
}
