// 第13章配套练习：模板匹配
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
    cv::Mat needle(12,10,CV_8U),image=cv::Mat::zeros(60,70,CV_8U),scores;cv::RNG rng(12345);rng.fill(needle,cv::RNG::UNIFORM,0,255);needle.copyTo(image(cv::Rect(23,17,needle.cols,needle.rows)));cv::matchTemplate(image,needle,scores,cv::TM_CCOEFF_NORMED);double maxVal;cv::Point location;cv::minMaxLoc(scores,nullptr,&maxVal,nullptr,&location);assert(location==cv::Point(23,17)&&maxVal>.99);
    std::cout<<"本章自检通过。\n";
}
