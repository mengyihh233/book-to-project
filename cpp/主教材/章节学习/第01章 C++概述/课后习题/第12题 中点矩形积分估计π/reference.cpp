#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>
#include <algorithm>
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid number");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected data");}

int main(){try{std::cout<<std::setprecision(10);end_input();const int rectangles=10000;const long double radius=2,width=radius/rectangles;long double sum=0;for(int i=0;i<rectangles;++i){long double x=(i+.5L)*width;sum+=width*std::sqrt(radius*radius-x*x);}std::cout<<sum<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
