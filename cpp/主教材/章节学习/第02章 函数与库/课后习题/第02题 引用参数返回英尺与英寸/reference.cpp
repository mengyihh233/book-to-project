#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <cassert>
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid finite number");return x;}
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected input");}
void metersToFeetInches(double meters,long long&feet,double&inches){
 if(meters<0||meters>1e9)throw std::runtime_error("length range");
 long double total=static_cast<long double>(meters)/.0254L;feet=static_cast<long long>(std::floor(total/12));inches=static_cast<double>(total-feet*12);
}

int main(){try{std::cout<<std::setprecision(12);double m=real();end_input();long long feet=0;double inches=0;metersToFeetInches(m,feet,inches);std::cout<<feet<<" "<<inches<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
