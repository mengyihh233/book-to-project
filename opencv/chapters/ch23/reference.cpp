// 第23章配套练习：建立复现记录
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
    std::string info=cv::getBuildInformation();assert(!info.empty());std::cout<<"版本："<<CV_VERSION<<"，线程数："<<cv::getNumThreads()<<"\n";
    std::cout<<"本章自检通过。\n";
}
