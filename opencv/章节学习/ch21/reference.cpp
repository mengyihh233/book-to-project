// 第21章配套练习：StatModel与SVM
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
    cv::Mat x=(cv::Mat_<float>(4,1)<<-2,-1,1,2),y=(cv::Mat_<int>(4,1)<<0,0,1,1);auto model=cv::ml::SVM::create();model->setType(cv::ml::SVM::C_SVC);model->setKernel(cv::ml::SVM::LINEAR);model->setC(1);assert(model->train(x,cv::ml::ROW_SAMPLE,y));cv::Mat a=(cv::Mat_<float>(1,1)<<-3),b=(cv::Mat_<float>(1,1)<<3);assert(model->predict(a)==0&&model->predict(b)==1);
    std::cout<<"本章自检通过。\n";
}
