#include "input.h"
#include "lesson.h"
int main() {
    try {
        std::string text;
        while(std::getline(std::cin,text)) {
            if(text.empty()) break;
            if(text.size()>10000) throw std::length_error("line too long");
            for(unsigned char c : text) if(c>127) throw std::invalid_argument("ASCII only");
            std::cout<<(isSentencePalindrome(text) ? "true" : "false")<<'\n';
        }
    } catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 2; }
}
