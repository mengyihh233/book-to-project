#pragma once
#include <vector>
#include <string>
#include <cstddef>
namespace hist {
class Histogram {
public:
    Histogram(int minimum,int maximum,int width=10);
    void add(int value);
    void addAll(const std::vector<int>& values);
    const std::vector<std::size_t>& counts() const {return counts_;}
    std::string render() const;
private:
    int minimum_,maximum_,width_;
    std::vector<std::size_t> counts_;
};
}
