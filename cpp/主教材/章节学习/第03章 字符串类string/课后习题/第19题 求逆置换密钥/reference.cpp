#include "input.h"
#include "lesson.h"
int main() { try { const auto key=line(); endInput(); std::cout<<invertKey(key)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
