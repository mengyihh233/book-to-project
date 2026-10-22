#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
double celsiusToFahrenheit(double c){double f=c*(9.0/5.0)+32;if(!std::isfinite(f))throw std::runtime_error("result overflow");return f;}
int main(){try{std::cout<<std::setprecision(12);double c=real();end_input();std::cout<<celsiusToFahrenheit(c)<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
