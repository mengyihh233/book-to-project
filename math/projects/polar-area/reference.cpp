#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
int main(){std::string kind,extra;double a=0;int n=0;
if(!(std::cin>>kind>>a>>n)||std::cin>>extra||!std::isfinite(a)||a<0||a>100||n<1||n>1000000)return 2;
if(kind!="circle"&&kind!="cardioid"&&kind!="rose3")return 2;
const double pi=std::acos(-1.0),end=kind=="rose3"?pi:2*pi,step=end/n;
double sum=0;for(int i=0;i<n;++i){const double theta=(i+0.5)*step;
const double r=kind=="circle"?a:kind=="cardioid"?a*(1+std::cos(theta)):a*std::sin(3*theta);sum+=r*r;}
const double area=sum*step/2,exact=pi*a*a*(kind=="circle"?1:kind=="cardioid"?1.5:0.25);
std::cout<<std::setprecision(15)<<"area="<<area<<" exact="<<exact<<" error="<<area-exact<<'\n';}
