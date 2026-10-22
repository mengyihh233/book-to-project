#include "input.h"
#include "lesson.h"
int main() { try { const auto str=line(); endInput(); std::cout << acronym(str) << "\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
