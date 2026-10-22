#include <iomanip>
#include <iostream>
#include <string>
int main(){int n=0;std::string extra;if(!(std::cin>>n)||std::cin>>extra||n<0||n>100000)return 2;
double geometric=0,term=1,telescoping=0;
for(int i=0;i<n;++i){geometric+=term;term/=3;const double j=i+1.0;telescoping+=1/(j*(j+1));}
std::cout<<std::setprecision(15)<<"geometric="<<geometric<<" telescoping="<<telescoping<<'\n';}
