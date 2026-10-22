#include "input.h"
#include "lesson.h"
int main() { try { const auto str=line(),remove=line(); endInput(); std::cout << removeCharacters(str,remove) << "\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
