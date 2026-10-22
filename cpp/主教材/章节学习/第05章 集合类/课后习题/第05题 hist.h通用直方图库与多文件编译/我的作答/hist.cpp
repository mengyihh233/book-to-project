#include "hist.h"
#include <stdexcept>
namespace hist {
Histogram::Histogram(int low,int high,int width):minimum_(low),maximum_(high),width_(width) {throw std::logic_error("TODO constructor");}
void Histogram::add(int) {throw std::logic_error("TODO add");}
void Histogram::addAll(const std::vector<int>&) {throw std::logic_error("TODO addAll");}
std::string Histogram::render() const {throw std::logic_error("TODO render");}
}
