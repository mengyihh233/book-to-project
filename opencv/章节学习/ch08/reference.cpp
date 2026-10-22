// 第8章配套练习：持久化参数
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
    cv::FileStorage out("params.yml",cv::FileStorage::WRITE|cv::FileStorage::MEMORY);cv::Mat k=cv::Mat::eye(3,3,CV_64F);out<<"threshold"<<42<<"camera"<<k;std::string text=out.releaseAndGetString();cv::FileStorage in(text,cv::FileStorage::READ|cv::FileStorage::MEMORY);int threshold=0;cv::Mat recovered;in["threshold"]>>threshold;in["camera"]>>recovered;assert(threshold==42&&cv::norm(k-recovered)==0);
    std::cout<<"本章自检通过。\n";
}
