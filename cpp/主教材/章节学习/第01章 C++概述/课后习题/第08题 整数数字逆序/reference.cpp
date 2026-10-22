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

int main(){try{std::cout<<std::setprecision(10);long long n=integer();end_input();if(n<0)throw std::runtime_error("nonnegative required");long long reversed=0;do{int digit=static_cast<int>(n%10);if(reversed>(std::numeric_limits<long long>::max()-digit)/10)throw std::runtime_error("reverse overflow");reversed=reversed*10+digit;n/=10;}while(n);std::cout<<reversed<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
