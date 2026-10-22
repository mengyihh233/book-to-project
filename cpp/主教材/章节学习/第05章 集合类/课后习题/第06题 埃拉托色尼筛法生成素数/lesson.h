#pragma once
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>
inline std::vector<int> primesUpTo(int limit) {
    if(limit<0||limit>1000000) throw std::out_of_range("limit 0..1000000");
    std::vector<unsigned char> composite(static_cast<std::size_t>(limit)+1);
    for(int p=2;p<=limit/p;++p) if(!composite[p])
        for(int multiple=p*p;multiple<=limit;multiple+=p) composite[multiple]=1;
    std::vector<int> primes;
    for(int value=2;value<=limit;++value) if(!composite[value]) primes.push_back(value);
    return primes;
}
