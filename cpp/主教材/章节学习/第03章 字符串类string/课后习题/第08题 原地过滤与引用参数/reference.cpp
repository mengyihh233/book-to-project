#include "input.h"
#include "lesson.h"
int main() { try { auto str=line(); const auto remove=line(); endInput(); removeCharactersInPlace(str,remove); std::cout << str << "\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
