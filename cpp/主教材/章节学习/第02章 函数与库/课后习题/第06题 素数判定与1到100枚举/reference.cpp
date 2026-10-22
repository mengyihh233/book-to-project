#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
bool isPrime(int n){if(n<2)return false;for(int d=2;d<=n/d;++d)if(n%d==0)return false;return true;}

int main(){try{std::cout<<std::setprecision(12);end_input();assert(!isPrime(-1));assert(!isPrime(0));assert(!isPrime(1));assert(isPrime(2));assert(!isPrime(91));bool first=true;for(int n=1;n<=100;++n)if(isPrime(n)){if(!first)std::cout<<" ";std::cout<<n;first=false;}std::cout<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
