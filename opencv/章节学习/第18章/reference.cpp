// 第18章配套练习：针孔相机投影
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
    cv::Mat k=(cv::Mat_<double>(3,3)<<100,0,50,0,100,50,0,0,1);std::vector<cv::Point3f>world{{0,0,2},{1,0,2},{0,1,2}};std::vector<cv::Point2f>pixels;cv::projectPoints(world,cv::Vec3d(0,0,0),cv::Vec3d(0,0,0),k,cv::noArray(),pixels);assert(cv::norm(pixels[0]-cv::Point2f(50,50))<1e-5);assert(cv::norm(pixels[1]-cv::Point2f(100,50))<1e-5);
    std::cout<<"本章自检通过。\n";
}
