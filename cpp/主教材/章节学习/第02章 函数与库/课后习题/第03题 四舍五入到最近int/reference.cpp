#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
int roundToNearestInt(double x){
 long double adjusted=x>=0?std::floor(static_cast<long double>(x)+.5L):std::ceil(static_cast<long double>(x)-.5L);
 if(adjusted<std::numeric_limits<int>::min()||adjusted>std::numeric_limits<int>::max())throw std::runtime_error("int overflow");
 return static_cast<int>(adjusted);
}

int main(){try{std::cout<<std::setprecision(12);double x=real();end_input();std::cout<<roundToNearestInt(x)<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
