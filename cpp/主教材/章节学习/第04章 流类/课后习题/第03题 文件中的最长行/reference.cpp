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
    std::string name, extra;
    if(!book_input::logicalLine(std::cin,name) || name.empty() || book_input::logicalLine(std::cin,extra)) return 2;
    std::ifstream in(std::filesystem::u8path(name),std::ios::binary);
    if(!in) { std::cerr << "Cannot open input file\n"; return 2; }
    std::string longest,line;
    while(std::getline(in,line)) {
        if(!in.eof() && !line.empty() && line.back()=='\r') line.pop_back();
        if(line.size()>longest.size()) longest=line;
    }
    if(in.bad()) return 2;
    std::cout << longest << '\n';
}
