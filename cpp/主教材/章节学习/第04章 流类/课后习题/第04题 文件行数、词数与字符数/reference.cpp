#include "../../../../教学辅助/input_line.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
int main() {
    std::string name,extra;
    if(!book_input::logicalLine(std::cin,name) || name.empty() || book_input::logicalLine(std::cin,extra)) return 2;
    std::ifstream in(std::filesystem::u8path(name),std::ios::binary);
    if(!in) { std::cerr << "Cannot open input file\n"; return 2; }
    unsigned long long lines=0,words=0,characters=0;
    bool inside=false,any=false;char ch=0,last=0;
    while(in.get(ch)) {
        // CRLF 作为一个逻辑换行；孤立 CR 是一个空白字符。
        if(ch=='\r' && in.peek()=='\n') continue;
        ++characters;any=true;last=ch;
        if(ch=='\n') ++lines;
        const bool space=ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\v' || ch=='\f';
        if(!space && !inside) ++words;
        inside=!space;
    }
    if(in.bad()) return 2;
    if(any && last!='\n') ++lines;
    std::cout << "Lines: " << std::setw(5) << lines << '\n'
              << "Words: " << std::setw(5) << words << '\n'
              << "Chars: " << std::setw(5) << characters << '\n';
}
