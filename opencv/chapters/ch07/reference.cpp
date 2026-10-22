// 第7章配套练习：并行函数对象
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
    cv::Mat image(16,16,CV_8U,cv::Scalar(0));image.at<uchar>(0,0)=255;struct Invert:cv::ParallelLoopBody{cv::Mat&m;explicit Invert(cv::Mat&v):m(v){}void operator()(const cv::Range&r)const override{for(int y=r.start;y<r.end;++y)for(int x=0;x<m.cols;++x)m.at<uchar>(y,x)=255-m.at<uchar>(y,x);}};cv::parallel_for_(cv::Range(0,image.rows),Invert(image));assert(image.at<uchar>(0,0)==0&&image.at<uchar>(1,1)==255);
    std::cout<<"本章自检通过。\n";
}
