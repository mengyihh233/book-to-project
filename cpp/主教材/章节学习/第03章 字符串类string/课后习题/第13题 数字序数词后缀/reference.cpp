#include "input.h"
#include "lesson.h"
int main() { try { const auto text=line(); endInput(); long long value=0; const auto parsed=std::from_chars(text.data(),text.data()+text.size(),value); if(parsed.ec!=std::errc{} || parsed.ptr!=text.data()+text.size()) throw std::invalid_argument("expected signed 64-bit integer"); std::cout<<createOrdinalForm(value)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
