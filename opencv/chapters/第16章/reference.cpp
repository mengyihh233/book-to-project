// 第16章配套练习：ORB特征与描述子
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
    cv::Mat texture(256,256,CV_8U);cv::RNG rng(123);rng.fill(texture,cv::RNG::UNIFORM,0,255);auto orb=cv::ORB::create(200);std::vector<cv::KeyPoint>keypoints;cv::Mat descriptors;orb->detectAndCompute(texture,cv::noArray(),keypoints,descriptors);assert(!keypoints.empty()&&descriptors.cols==32&&descriptors.type()==CV_8U);std::cout<<"关键点数："<<keypoints.size()<<"\n";
    std::cout<<"本章自检通过。\n";
}
