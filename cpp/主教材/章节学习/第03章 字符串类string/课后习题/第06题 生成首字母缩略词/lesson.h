#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
inline bool asciiLetter(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z'); }
inline std::string acronym(const std::string& phrase) {
    bool inWord=false; std::string result;
    for (char c : phrase) {
        if (asciiLetter(c)) {
            if (!inWord) result+=c>='a' && c<='z' ? static_cast<char>(c-'a'+'A') : c;
            inWord=true;
        } else inWord=false;
    }
    return result;
}
