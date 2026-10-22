// 第14章配套练习：轮廓与包围盒
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
    cv::Mat image=cv::Mat::zeros(80,100,CV_8U);cv::rectangle(image,cv::Rect(10,20,30,25),cv::Scalar(255),-1);std::vector<std::vector<cv::Point>>contours;cv::findContours(image,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);assert(contours.size()==1);assert(cv::boundingRect(contours[0])==cv::Rect(10,20,30,25));
    std::cout<<"本章自检通过。\n";
}
