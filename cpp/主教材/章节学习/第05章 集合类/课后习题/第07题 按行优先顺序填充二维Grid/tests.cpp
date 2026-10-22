#include "lesson.h"
#include <cassert>
int main(){
IntGrid grid(2,3);fillGrid(grid,{1,2,3,4,5,6});assert(grid.at(0,2)==3&&grid.at(1,0)==4);bool error=false;try{fillGrid(grid,{9});}catch(const std::exception&){error=true;}assert(error&&grid.at(0,0)==1);
}
