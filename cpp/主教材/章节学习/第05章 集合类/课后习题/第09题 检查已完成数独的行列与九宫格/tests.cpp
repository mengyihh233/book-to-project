#include "lesson.h"
#include <cassert>
int main(){
IntGrid g(9,9);for(int r=0;r<9;++r)for(int c=0;c<9;++c)g.at(r,c)=(r*3+r/3+c)%9+1;assert(checkSudokuSolution(g));g.at(0,0)=0;assert(!checkSudokuSolution(g));bool error=false;try{IntGrid wrong(1,1);checkSudokuSolution(wrong);}catch(const std::exception&){error=true;}assert(error);
}
