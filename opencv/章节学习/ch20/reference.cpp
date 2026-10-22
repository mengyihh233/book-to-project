// 第20章配套练习：训练与测试分离
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
    cv::Mat x=(cv::Mat_<float>(4,1)<<-2,-1,1,2),y=(cv::Mat_<float>(4,1)<<0,0,1,1);auto model=cv::ml::KNearest::create();model->train(x,cv::ml::ROW_SAMPLE,y);cv::Mat query=(cv::Mat_<float>(2,1)<<-1.5,1.5),prediction;model->findNearest(query,1,prediction);assert(prediction.at<float>(0)==0&&prediction.at<float>(1)==1);
    std::cout<<"本章自检通过。\n";
}
