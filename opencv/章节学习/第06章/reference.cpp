// 第6章配套练习：绘制可验证的标注
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
    cv::Mat img=cv::Mat::zeros(100,120,CV_8U);cv::rectangle(img,cv::Rect(10,20,30,40),cv::Scalar(255),-1);cv::circle(img,{80,50},10,cv::Scalar(255),-1);assert(img.at<uchar>(20,10)==255&&img.at<uchar>(0,0)==0);assert(cv::countNonZero(img)>1200);
    std::cout<<"本章自检通过。\n";
}
