#pragma once
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>
inline void fillGrid(IntGrid& grid,const std::vector<int>& values) {
    if(values.size()!=static_cast<std::size_t>(grid.rows())*grid.cols()) throw std::invalid_argument("value count must equal grid size");
    std::size_t index=0;
    for(int row=0;row<grid.rows();++row)
        for(int col=0;col<grid.cols();++col) grid.at(row,col)=values[index++];
}
