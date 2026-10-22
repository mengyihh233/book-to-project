// 第2章配套练习：图像读取的离线练习
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
    cv::Mat image(20,30,CV_8UC3,cv::Scalar(10,20,30));std::vector<uchar>bytes;assert(cv::imencode(".png",image,bytes));cv::Mat decoded=cv::imdecode(bytes,cv::IMREAD_COLOR);assert(!decoded.empty()&&decoded.size()==image.size());assert(decoded.at<cv::Vec3b>(0,0)==cv::Vec3b(10,20,30));
    std::cout<<"本章自检通过。\n";
}
