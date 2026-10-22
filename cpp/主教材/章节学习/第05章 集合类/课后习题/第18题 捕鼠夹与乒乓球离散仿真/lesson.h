#pragma once
#include "../../../../教学辅助/input_line.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// 第18题：整轮落地，整轮生成下一批；不能让新球在本轮继续落地。
struct ChainResult { int rounds=0, triggered=0, peak=1, landings=0, traps=0; };
inline ChainResult simulateChain(std::istream& in) {
    std::string line, mode, seedText, extra;
    int side=0;
    if(!book_input::logicalLine(in,line)) throw std::invalid_argument("missing header");
    std::istringstream header(line);
    if(!(header>>mode>>side) || side<1 || side>25) throw std::invalid_argument("side must be 1..25");
    std::uint32_t state=0;
    if(mode=="random") {
        if(!(header>>seedText) || seedText.empty() || seedText.size()>10) throw std::invalid_argument("missing seed");
        std::uint64_t seed=0;
        for(char c:seedText) { if(c<'0'||c>'9') throw std::invalid_argument("invalid seed"); seed=seed*10+static_cast<unsigned>(c-'0'); }
        if(seed>UINT32_MAX) throw std::invalid_argument("seed too large");
        state=static_cast<std::uint32_t>(seed);
    } else if(mode!="trace") throw std::invalid_argument("mode must be trace or random");
    if(header>>extra) throw std::invalid_argument("extra header field");
    const int count=side*side;
    std::vector<bool> triggered(static_cast<std::size_t>(count),false);
    int airborne=1;
    ChainResult result;
    result.traps=count;
    while(airborne>0) {
        std::vector<int> targets;
        if(mode=="trace") {
            if(!book_input::logicalLine(in,line)) throw std::invalid_argument("missing landing round");
            std::istringstream row(line);
            for(int i=0;i<airborne;++i) {
                int target=-1;
                if(!(row>>target)||target<0||target>=count) throw std::invalid_argument("invalid landing target");
                targets.push_back(target);
            }
            if(row>>extra) throw std::invalid_argument("extra landing target");
        } else {
            const std::uint64_t range=std::uint64_t{1}<<32;
            const auto limit=range-range%static_cast<unsigned>(count);
            for(int i=0;i<airborne;++i) {
                do {state=state*1664525u+1013904223u;} while(static_cast<std::uint64_t>(state)>=limit);
                targets.push_back(static_cast<int>(state%static_cast<unsigned>(count)));
            }
        }
        int fresh=0;
        for(int target:targets) {
            if(!triggered[static_cast<std::size_t>(target)]) {
                triggered[static_cast<std::size_t>(target)]=true;
                ++fresh;
            }
        }
        ++result.rounds;
        result.landings+=airborne;
        result.triggered+=fresh;
        airborne=2*fresh;
        if(airborne>result.peak) result.peak=airborne;
    }
    if(book_input::logicalLine(in,line)) throw std::invalid_argument("extra input after termination");
    return result;
}
inline void printChain(const ChainResult& r,std::ostream& out) {
    out<<"rounds="<<r.rounds<<" triggered="<<r.triggered<<" peak="<<r.peak<<" landings="<<r.landings<<'\n';
    out<<std::fixed<<std::setprecision(6)<<"percent="<<(100.0*r.triggered/r.traps)<<'\n';
}
