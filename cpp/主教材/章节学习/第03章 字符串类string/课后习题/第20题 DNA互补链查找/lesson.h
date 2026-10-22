#pragma once
#include <string>
#include <stdexcept>
inline char lower(char c) { return c>='A' && c<='Z' ? static_cast<char>(c-'A'+'a') : c; }
inline char upper(char c) { return c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c; }
inline bool letter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline bool vowel(char c) { return std::string("aeiou").find(lower(c))!=std::string::npos; }
inline char complement(char c) {
    switch(upper(c)) { case 'A':return 'T';case 'T':return 'A';case 'C':return 'G';case 'G':return 'C'; }
    throw std::invalid_argument("DNA alphabet must be A/C/G/T");
}
inline int findDNAMatch(std::string shortDNA,std::string longDNA,int start=0) {
    if(start<0) throw std::invalid_argument("start must be nonnegative");
    for(char& c : shortDNA) c=complement(c);
    for(char& c : longDNA) { (void)complement(c);c=upper(c); }
    const auto found=longDNA.find(shortDNA,static_cast<std::size_t>(start));
    return found==std::string::npos ? -1 : static_cast<int>(found);
}
