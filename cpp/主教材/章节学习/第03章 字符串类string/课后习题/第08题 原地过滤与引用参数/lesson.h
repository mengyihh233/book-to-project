#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
// remove按值复制：即使调用removeCharactersInPlace(s,s)，删除集也保持稳定。
inline void removeCharactersInPlace(std::string& str,std::string remove) {
    std::size_t write=0;
    for (std::size_t read=0;read<str.size();++read)
        if (remove.find(str[read])==std::string::npos) str[write++]=str[read];
    str.resize(write);
}
