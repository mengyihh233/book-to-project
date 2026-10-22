#include "hist.h"
#include <stdexcept>
#include <cassert>
int main(){
hist::Histogram h(-10,10,10);h.addAll({-10,0,10});assert((h.counts()==std::vector<std::size_t>{1,1,1}));auto before=h.counts();bool error=false;try{h.addAll({0,11});}catch(const std::exception&){error=true;}assert(error&&h.counts()==before);
}
