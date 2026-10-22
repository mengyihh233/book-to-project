#include "lesson.h"
#include <cassert>
int main(){
IntGrid g(2,3);for(int r=0;r<2;++r)for(int c=0;c<3;++c)g.at(r,c)=r*3+c+1;reshape(g,3,3);assert(g.at(1,0)==4&&g.at(2,0)==0);bool error=false;try{reshape(g,-1,3);}catch(const std::exception&){error=true;}assert(error&&g.rows()==3);reshape(g,0,5);assert(g.rows()==0&&g.cols()==5);
}
