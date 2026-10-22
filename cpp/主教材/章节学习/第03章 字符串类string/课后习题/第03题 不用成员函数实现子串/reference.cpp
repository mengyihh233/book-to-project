#include "input.h"
#include "lesson.h"
int main() { try { const auto str=line(); const auto pos=indexValue(line()); const auto count=line(); endInput(); std::cout << (count=="ALL" ? substr(str,pos) : substr(str,pos,indexValue(count))) << "\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
