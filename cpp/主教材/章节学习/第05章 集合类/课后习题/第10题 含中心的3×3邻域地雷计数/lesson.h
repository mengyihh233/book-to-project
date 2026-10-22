#pragma once
#include "../../../../教学辅助/grid_lesson.h"
inline void fixCounts(const IntGrid& mines,IntGrid& counts) {
    for(int r=0;r<mines.rows();++r) for(int c=0;c<mines.cols();++c)
        if(mines.at(r,c)!=0&&mines.at(r,c)!=1) throw std::invalid_argument("mine cells must be 0 or 1");
    IntGrid result(mines.rows(),mines.cols());
    for(int r=0;r<mines.rows();++r) for(int c=0;c<mines.cols();++c) {
        int sum=0;
        for(int dr=-1;dr<=1;++dr) for(int dc=-1;dc<=1;++dc) {
            int nr=r+dr,nc=c+dc;
            if(nr>=0&&nr<mines.rows()&&nc>=0&&nc<mines.cols()) sum+=mines.at(nr,nc);
        }
        result.at(r,c)=sum;
    }
    counts=std::move(result);
}
