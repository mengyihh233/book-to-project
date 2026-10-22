#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
bool isPerfect(int n){
 if(n<2)return false;
 int total=1;
 for(int d=2;d<=n/d;++d)if(n%d==0){total+=d;if(d!=n/d)total+=n/d;}
 return total==n;
}

int main(){try{std::cout<<std::setprecision(12);end_input();assert(!isPerfect(1));assert(isPerfect(6));assert(isPerfect(28));assert(!isPerfect(12));bool first=true;for(int n=1;n<=9999;++n)if(isPerfect(n)){if(!first)std::cout<<" ";std::cout<<n;first=false;}std::cout<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
