#include "input.h"
#include "lesson.h"
int main() { try { const auto word=line(); endInput(); std::cout<<obenglobish(word)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
