// 第17章配套练习：稀疏光流
// 独立参考实现，非原书官方答案。
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int main(){
    cv::setNumThreads(1); // 保持小型教学实验的运行条件稳定。
    cv::Mat a=cv::Mat::zeros(120,120,CV_8U),b;for(int y=20;y<=80;y+=20)for(int x=20;x<=80;x+=20)cv::rectangle(a,cv::Rect(x,y,6,6),cv::Scalar(255),-1);cv::Mat m=(cv::Mat_<double>(2,3)<<1,0,3,0,1,2);cv::warpAffine(a,b,m,a.size());std::vector<cv::Point2f>p,q;cv::goodFeaturesToTrack(a,p,40,.01,8);std::vector<uchar>status;std::vector<float>error;cv::calcOpticalFlowPyrLK(a,b,p,q,status,error);int count=0;double dx=0,dy=0;for(size_t i=0;i<p.size();++i)if(status[i]){dx+=q[i].x-p[i].x;dy+=q[i].y-p[i].y;++count;}assert(count>0&&std::abs(dx/count-3)<.2&&std::abs(dy/count-2)<.2);
    std::cout<<"本章自检通过。\n";
}
