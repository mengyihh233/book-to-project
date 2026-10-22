#include "input.h"
#include "lesson.h"
int main() { try { const auto str=line(),suffix=line(); endInput(); std::cout << (endsWith(str,suffix) ? "true" : "false") << "\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
