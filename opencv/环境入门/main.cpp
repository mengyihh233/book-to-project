#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdexcept>
int main(){
    // 使用合成图像，避免依赖摄像头和外部照片。
    cv::Mat source(300,400,CV_8UC3,cv::Scalar(25,25,25));
    cv::rectangle(source,{40,50},{180,240},{40,210,70},-1);
    cv::circle(source,{290,150},65,{220,110,30},-1);
    cv::Mat gray,blurred,edges,preview;
    cv::cvtColor(source,gray,cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray,blurred,{5,5},1.2);
    cv::Canny(blurred,edges,50,120);
    if(cv::countNonZero(edges)==0)throw std::runtime_error("没有检测到边缘");
    cv::cvtColor(edges,preview,cv::COLOR_GRAY2BGR);
    cv::Mat combined;cv::hconcat(source,preview,combined);
    const std::string path="D:/Book-Learning/opencv/output/first-edges.png";
    if(!cv::imwrite(path,combined))throw std::runtime_error("输出保存失败");
    std::cout<<"OpenCV版本："<<CV_VERSION<<"\n边缘像素数："<<cv::countNonZero(edges)<<"\n结果："<<path<<"\n";
}
