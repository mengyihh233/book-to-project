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

int main(){try{std::cout<<std::setprecision(10);long long n=integer();end_input();if(n<2||n>1000000000000LL)throw std::runtime_error("factor range");bool first=true;for(long long p=2;p<=n/p;++p)while(n%p==0){if(!first)std::cout<<" ";std::cout<<p;first=false;n/=p;}if(n>1){if(!first)std::cout<<" ";std::cout<<n;}std::cout<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
