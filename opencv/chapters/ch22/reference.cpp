// 第22章配套练习：检测器结构检查
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
    cv::HOGDescriptor hog;auto detector=cv::HOGDescriptor::getDefaultPeopleDetector();assert(detector.size()==hog.getDescriptorSize()+1);hog.setSVMDetector(detector);cv::Mat patch(hog.winSize,CV_8U,cv::Scalar(0));std::vector<float>features;hog.compute(patch,features);assert(features.size()==hog.getDescriptorSize());
    std::cout<<"本章自检通过。\n";
}
