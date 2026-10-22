#include "lesson.h"
#include <cassert>
int main(){
IntGrid mines(3,3),out(1,1);for(int r=0;r<3;++r)for(int c=0;c<3;++c)mines.at(r,c)=1;fixCounts(mines,out);assert(out.at(1,1)==9&&out.at(0,0)==4&&out.at(0,1)==6);fixCounts(mines,mines);assert(mines.at(1,1)==9);
}
