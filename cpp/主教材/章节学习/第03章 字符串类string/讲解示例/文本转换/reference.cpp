#include <iostream>
#include <iomanip>
#include <cassert>
#include "../../课后习题/第09题/lesson.h"
#include "../../课后习题/第10题/lesson.h"
#include "../../课后习题/第11题/lesson.h"
int main() {
    const std::string source="  boookkeeper  ";
    const auto compressed=removeDoubledLetters(source);
    const auto changed=replaceAll(compressed,std::string("bok"),std::string("note"));
    assert(compressed==" bokeper " && changed==" noteeper ");
    assert(source=="  boookkeeper  ");
    std::cout<<"source="<<std::quoted(source)<<'\n';
    std::cout<<"compressed="<<std::quoted(compressed)<<'\n';
    std::cout<<"replaced="<<std::quoted(changed)<<'\n';
    const auto grown=replaceAll("aa",std::string("a"),std::string("aa"));
    assert(grown=="aaaa");std::cout<<"nonrecursive="<<std::quoted(grown)<<'\n';
    assert(isSentencePalindrome("Madam, I'm Adam."));
    std::cout<<"sentence=true\n";
}
