#pragma once
#include "../../../../教学辅助/vector_lesson.h"
template<class T> void readBlock(std::istream& in,std::vector<T>& values) {
    std::vector<T> next;std::string line;
    while(book_input::logicalLine(in,line) && !line.empty()) {
        if(line.size()>10000 || next.size()>=10000) throw std::length_error("block size");
        for(unsigned char c:line) if(c>127) throw std::invalid_argument("ASCII record required");
        if constexpr(std::is_same_v<T,std::string>) next.push_back(line);
        else next.push_back(strictNumber<T>(line));
    }
    if(in.bad()) throw std::runtime_error("read failure");
    values=std::move(next);
}
inline void readVector(std::istream& in,std::vector<int>& data) {readBlock(in,data);}
inline void readVector(std::istream& in,std::vector<double>& data) {readBlock(in,data);}
inline void readVector(std::istream& in,std::vector<std::string>& data) {readBlock(in,data);}
template<class T> void displayBlocks(std::istream& in,std::ostream& out,int calls) {
    std::vector<T> data;
    for(int k=0;k<calls;++k) {
        readVector(in,data);out<<data.size()<<'\n';
        for(const auto& item:data) out<<std::setprecision(17)<<item<<'\n';
    }
}
