#include "input.h"
#include "lesson.h"
int main() { try { const auto s=line(); endInput(); std::cout<<createRegularPlural(s)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
