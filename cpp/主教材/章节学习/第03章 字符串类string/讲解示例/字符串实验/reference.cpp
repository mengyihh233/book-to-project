#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
int main() {
    std::istringstream words("Ada Lovelace"), lines("Ada Lovelace");
    std::string word,line; words>>word; std::getline(lines,line);
    assert(word=="Ada" && line=="Ada Lovelace");
    std::cout<<"word=["<<word<<"] line=["<<line<<"]\n";
    std::string original="orbit", copy=original; copy.at(0)='O';
    assert(original=="orbit" && copy=="Orbit");
    std::cout<<"original="<<original<<" copy="<<copy<<"\n";
    assert(original.substr(original.size()).empty());
    bool rejected=false;
    try { (void)original.at(original.size()); } catch(const std::out_of_range&) { rejected=true; }
    assert(rejected);
    std::cout<<"substr(size)=[] at(size)=out_of_range\n";
    const auto found=original.find('z'); assert(found==std::string::npos);
    std::cout<<"find(z)=npos\n";
    std::string reversed;
    for(std::size_t i=original.size();i>0;--i) reversed+=original[i-1];
    assert(reversed=="tibro");std::cout<<"reverse="<<reversed<<"\n";
}
