#include "input.h"
#include "lesson.h"
int main() { try { const auto mode=line(),s=line(),from=line(),to=line(); endInput(); if(mode=="char") { if(from.size()!=1 || to.size()!=1) throw std::invalid_argument("char mode requires two single characters"); std::cout<<replaceAll(s,from[0],to[0])<<"\n"; } else if(mode=="string") std::cout<<replaceAll(s,from,to)<<"\n"; else throw std::invalid_argument("expected char or string mode"); } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
