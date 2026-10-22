#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline int scrabbleScore(const std::string& word) {
    constexpr int points[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    int total=0;
    for (char c : word) {
        if (c>='a' && c<='z') c=static_cast<char>(c-'a'+'A');
        if (c>='A' && c<='Z') total+=points[c-'A'];
    }
    return total;
}
