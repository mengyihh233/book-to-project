#include "hist.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cstdint>
namespace hist {
Histogram::Histogram(int minimum,int maximum,int width):minimum_(minimum),maximum_(maximum),width_(width) {
    if(minimum>maximum || width<=0) throw std::invalid_argument("invalid histogram range");
    std::int64_t count=(static_cast<std::int64_t>(maximum)-minimum)/width+1;
    if(count>200) throw std::length_error("at most 200 bins");
    counts_.resize(static_cast<std::size_t>(count));
}
void Histogram::add(int value) {
    if(value<minimum_||value>maximum_) throw std::out_of_range("value outside histogram range");
    auto index=(static_cast<std::int64_t>(value)-minimum_)/width_;
    ++counts_.at(static_cast<std::size_t>(index));
}
void Histogram::addAll(const std::vector<int>& values) {
    for(int value:values) if(value<minimum_||value>maximum_) throw std::out_of_range("value outside histogram range");
    for(int value:values) add(value);
}
std::string Histogram::render() const {
    std::ostringstream out;
    for(std::size_t i=0;i<counts_.size();++i) {
        auto low=static_cast<std::int64_t>(minimum_)+static_cast<std::int64_t>(i)*width_;
        auto high=std::min(static_cast<std::int64_t>(maximum_),low+width_-1);
        out<<low<<".."<<high<<": "<<std::string(counts_[i],'*')<<'\n';
    }
    return out.str();
}
}
