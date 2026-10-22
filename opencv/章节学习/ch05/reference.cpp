// 第5章配套练习：饱和加法与数值转换
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
    cv::Mat a(1,1,CV_8U,cv::Scalar(250)),b;cv::add(a,cv::Scalar(10),b);assert(b.at<uchar>(0,0)==255);assert(static_cast<uchar>(250+10)==4);cv::Mat floating;a.convertTo(floating,CV_32F,1./255);assert(std::abs(floating.at<float>(0,0)-250.f/255)<1e-6);
    std::cout<<"本章自检通过。\n";
}
