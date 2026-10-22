// 第11章配套练习：仿射平移
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
    cv::Mat src=cv::Mat::zeros(12,12,CV_8U),dst;src.at<uchar>(3,2)=255;cv::Mat transform=(cv::Mat_<double>(2,3)<<1,0,4,0,1,2);cv::warpAffine(src,dst,transform,src.size(),cv::INTER_NEAREST);assert(dst.at<uchar>(5,6)==255&&cv::countNonZero(dst)==1);
    std::cout<<"本章自检通过。\n";
}
