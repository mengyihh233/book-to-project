// 第12章配套练习：边缘与直线
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
    cv::Mat image=cv::Mat::zeros(120,120,CV_8U),edges;cv::rectangle(image,cv::Rect(20,20,80,80),cv::Scalar(255),2);cv::Canny(image,edges,50,150);std::vector<cv::Vec4i>lines;cv::HoughLinesP(edges,lines,1,CV_PI/180,20,30,5);assert(cv::countNonZero(edges)>0&&!lines.empty());std::cout<<"检测直线数："<<lines.size()<<"\n";
    std::cout<<"本章自检通过。\n";
}
