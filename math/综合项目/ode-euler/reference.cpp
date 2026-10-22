#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
int main(){int n=0;double t=0,y=0,k=0;std::string extra;
if(!(std::cin>>n>>t>>y>>k)||std::cin>>extra||n<1||n>10000||!std::isfinite(t)||!std::isfinite(y)||!std::isfinite(k)||t<0||t>20||std::abs(y)>100||std::abs(k)>5)return 2;
const double exact=y*std::exp(k*t),step=t/n;
for(int i=0;i<n;++i)y+=step*k*y;
if(!std::isfinite(y)||!std::isfinite(exact))return 2;
std::cout<<std::setprecision(15)<<"euler="<<y<<" exact="<<exact<<" error="<<y-exact<<'\n';}
