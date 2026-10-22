#include "input.h"
#include "lesson.h"
int main() { try { const auto text=line(),amount=line(); endInput(); long long shift=0; const auto parsed=std::from_chars(amount.data(),amount.data()+amount.size(),shift); if(parsed.ec!=std::errc{} || parsed.ptr!=amount.data()+amount.size()) throw std::invalid_argument("expected signed 64-bit shift"); std::cout<<encodeCaesarCipher(text,shift)<<"\n"; } catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; } }
