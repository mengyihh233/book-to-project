// 第9章配套练习：交互回调逻辑
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
    struct State{int threshold=0;};auto callback=[](int value,void*ptr){auto&s=*static_cast<State*>(ptr);s.threshold=std::max(0,std::min(255,value));};State state;callback(300,&state);assert(state.threshold==255);callback(-3,&state);assert(state.threshold==0);
    std::cout<<"本章自检通过。\n";
}
