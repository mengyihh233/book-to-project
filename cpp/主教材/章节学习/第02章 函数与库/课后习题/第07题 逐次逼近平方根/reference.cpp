#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
double iterativeSqrt(double x){
 if(x<0)throw std::runtime_error("negative square root");
 if(x==0)return 0;
 double guess=x/2;if(guess==0)guess=1;double previous=-1;
 for(int i=0;i<2048;++i){double next=.5*guess+.5*(x/guess);if(next==guess||next==previous)return next;previous=guess;guess=next;}
 throw std::runtime_error("iteration limit");
}

int main(){try{std::cout<<std::setprecision(12);double x=real();end_input();std::cout<<iterativeSqrt(x)<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
