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

int main(){try{std::cout<<std::setprecision(10);double m=real();end_input();if(m<0||m>1e9)throw std::runtime_error("length range");double total=m/.0254;long long feet=static_cast<long long>(std::floor(total/12));double inches=total-feet*12;if(std::abs(inches)<1e-8)inches=0;if(std::abs(inches-12)<1e-8){++feet;inches=0;}std::cout<<feet<<" "<<inches<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
