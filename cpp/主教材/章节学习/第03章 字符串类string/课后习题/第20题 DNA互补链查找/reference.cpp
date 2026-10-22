#include "input.h"
#include "lesson.h"
int main() { try { const auto shortDNA=line(),longDNA=line(),position=line(); endInput(); std::cout<<(position=="DEFAULT" ? findDNAMatch(shortDNA,longDNA) : findDNAMatch(shortDNA,longDNA,static_cast<int>(indexValue(position))))<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
