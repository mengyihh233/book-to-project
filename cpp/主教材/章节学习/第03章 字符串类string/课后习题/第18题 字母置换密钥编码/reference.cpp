#include "input.h"
#include "lesson.h"
int main() { try { const auto key=line(),text=line(); endInput(); std::cout<<encodeSubstitution(text,key)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
