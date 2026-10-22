#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
double windChill(double t,double v){
 if(t>40||v<0)throw std::runtime_error("wind chill domain");
 if(v==0)return t;
 double factor=std::pow(v,.16);double value=35.74+.6215*t-35.75*factor+.4275*t*factor;
 if(!std::isfinite(value))throw std::runtime_error("result overflow");
 return value;
}

int main(){try{std::cout<<std::setprecision(12);double t=real(),v=real();end_input();std::cout<<windChill(t,v)<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
