// 第15章配套练习：背景减除
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
    auto model=cv::createBackgroundSubtractorMOG2(100,16,false);cv::Mat bg(80,100,CV_8UC3,cv::Scalar(30,30,30)),mask;for(int i=0;i<20;++i)model->apply(bg,mask,.2);cv::Mat frame=bg.clone();cv::rectangle(frame,cv::Rect(30,20,20,20),cv::Scalar(200,200,200),-1);model->apply(frame,mask,0);assert(cv::countNonZero(mask)>200);
    std::cout<<"本章自检通过。\n";
}
