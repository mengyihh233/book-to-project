// 第10章配套练习：平滑与形态学
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
    cv::Mat impulse=cv::Mat::zeros(9,9,CV_8U);impulse.at<uchar>(4,4)=255;cv::Mat blurred,opened;cv::GaussianBlur(impulse,blurred,{3,3},1);assert(blurred.at<uchar>(4,4)>0&&blurred.at<uchar>(4,4)<255);cv::morphologyEx(impulse,opened,cv::MORPH_OPEN,cv::getStructuringElement(cv::MORPH_RECT,{3,3}));assert(cv::countNonZero(opened)==0);
    std::cout<<"本章自检通过。\n";
}
