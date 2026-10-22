#include "input.h"
#include "lesson.h"
int main() { try { const auto text=line(); endInput(); std::cout<<lineToPigLatin(text)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
