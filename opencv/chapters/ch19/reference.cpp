// 第19章配套练习：双目三角化
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
    cv::Mat p1=(cv::Mat_<double>(3,4)<<1,0,0,0,0,1,0,0,0,0,1,0),p2=p1.clone();p2.at<double>(0,3)=-1;cv::Mat a=(cv::Mat_<double>(2,1)<<0,0),b=(cv::Mat_<double>(2,1)<<-.2,0),homogeneous;cv::triangulatePoints(p1,p2,a,b,homogeneous);double z=homogeneous.at<double>(2,0)/homogeneous.at<double>(3,0);assert(std::abs(z-5)<1e-6);
    std::cout<<"本章自检通过。\n";
}
