// 第3章配套练习：类型与通道
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
    cv::Mat rgb(2,3,CV_8UC3,cv::Scalar(1,2,3)),f(2,3,CV_32FC1,cv::Scalar(.5));assert(rgb.channels()==3&&rgb.depth()==CV_8U);assert(rgb.at<cv::Vec3b>(1,2)[2]==3);assert(f.at<float>(0,0)==.5f);
    std::cout<<"本章自检通过。\n";
}
