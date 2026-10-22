#pragma once
#include "../../../../教学辅助/grid_lesson.h"
inline void reshape(IntGrid& grid,int newRows,int newCols) {
    IntGrid result(newRows,newCols);
    int count=std::min(grid.rows()*grid.cols(),newRows*newCols);
    for(int i=0;i<count;++i) result.at(i/newCols,i%newCols)=grid.at(i/grid.cols(),i%grid.cols());
    grid=std::move(result);
}
