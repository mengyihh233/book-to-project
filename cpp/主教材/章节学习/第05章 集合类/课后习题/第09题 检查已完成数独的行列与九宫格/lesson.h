#pragma once
#include "../../../../教学辅助/grid_lesson.h"
inline bool checkSudokuSolution(const IntGrid& puzzle) {
    if(puzzle.rows()!=9||puzzle.cols()!=9) throw std::invalid_argument("Sudoku must be 9 by 9");
    for(int r=0;r<9;++r) for(int c=0;c<9;++c) if(puzzle.at(r,c)<1||puzzle.at(r,c)>9) return false;
    for(int i=0;i<9;++i) {
        unsigned row=0,col=0,box=0;
        for(int j=0;j<9;++j) {
            unsigned a=1U<<puzzle.at(i,j),b=1U<<puzzle.at(j,i);
            unsigned k=1U<<puzzle.at((i/3)*3+j/3,(i%3)*3+j%3);
            if((row&a)||(col&b)||(box&k)) return false;
            row|=a;col|=b;box|=k;
        }
    }
    return true;
}
