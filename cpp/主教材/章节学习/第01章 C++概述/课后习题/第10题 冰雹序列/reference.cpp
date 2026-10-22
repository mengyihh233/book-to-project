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

int main(){try{std::cout<<std::setprecision(10);long long n=integer();end_input();if(n<1)throw std::runtime_error("positive required");std::vector<long long> values{n};while(n!=1){if(values.size()>1000000)throw std::runtime_error("step limit");if(n%2==0)n/=2;else{if(n>(std::numeric_limits<long long>::max()-1)/3)throw std::runtime_error("overflow");n=3*n+1;}values.push_back(n);}for(std::size_t i=0;i<values.size();++i){if(i)std::cout<<" ";std::cout<<values[i];}std::cout<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
