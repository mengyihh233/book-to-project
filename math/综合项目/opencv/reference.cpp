#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
int main(){int n=0;std::string extra;if(!(std::cin>>n)||std::cin>>extra||n<3||n>101||n%2==0)return 2;
cv::Mat image(n,n,CV_64F);for(int v=0;v<n;++v)for(int u=0;u<n;++u)image.at<double>(v,u)=2*u+3*v;
cv::Mat dx,dy;cv::Sobel(image,dx,CV_64F,1,0,3,1.0/8,0,cv::BORDER_REFLECT_101);cv::Sobel(image,dy,CV_64F,0,1,3,1.0/8,0,cv::BORDER_REFLECT_101);
const double x=dx.at<double>(n/2,n/2),y=dy.at<double>(n/2,n/2);
std::cout<<std::setprecision(15)<<"du="<<x<<" dv="<<y<<" magnitude="<<std::hypot(x,y)<<'\n';}
