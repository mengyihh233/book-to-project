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

int main(){try{std::cout<<std::setprecision(10);bool first=false,second=false;long long a=0,b=0;for(;;){long long x=integer();if(x==0)break;if(!first){a=x;first=true;}else if(x>=a){b=a;a=x;second=true;}else if(!second||x>b){b=x;second=true;}}end_input();if(!second)throw std::runtime_error("need two observations");std::cout<<a<<" "<<b<<"\n";
return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}}
