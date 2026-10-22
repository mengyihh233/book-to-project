// Learning OpenCV 第4章习题2：积分图(a-d)，(e)见solution.md。
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
static void check(bool ok,const char*m){if(!ok)throw std::runtime_error(m);}
cv::Mat prefix(const cv::Mat&image){
    check(image.type()==CV_8UC1&&!image.empty(),"expect nonempty CV_8UC1");
    cv::Mat result=cv::Mat::zeros(image.size(),CV_32FC1);
    for(int y=0;y<image.rows;++y)for(int x=0;x<image.cols;++x){
        float left=x?result.at<float>(y,x-1):0,up=y?result.at<float>(y-1,x):0,diag=(x&&y)?result.at<float>(y-1,x-1):0;
        result.at<float>(y,x)=image.at<uchar>(y,x)+left+up-diag;
    }
    return result;
}
double rectangle_sum(const cv::Mat&p,cv::Rect box){
    check(p.type()==CV_32FC1,"expect float prefix");
    check(box.x>=0&&box.y>=0&&box.width>0&&box.height>0&&box.x<=p.cols-box.width&&box.y<=p.rows-box.height,"invalid rectangle");
    auto at=[&](int y,int x)->double{return x<0||y<0?0:p.at<float>(y,x);};
    int x1=box.x-1,y1=box.y-1,x2=box.x+box.width-1,y2=box.y+box.height-1;
    return at(y2,x2)-at(y1,x2)-at(y2,x1)+at(y1,x1);
}
int main(){try{
    // 宽200、高100；总和最多5100000，单精度仍能精确表示这些整数。
    cv::RNG rng(20261019);cv::Mat image(100,200,CV_8UC1);rng.fill(image,cv::RNG::UNIFORM,0,256);const auto p=prefix(image);
    int passed=0;
    auto verify=[&](cv::Rect r){check(std::abs(rectangle_sum(p,r)-cv::sum(image(r))[0])<.001,"rectangle sum mismatch");++passed;};
    verify({0,0,200,100});verify({0,0,1,1});verify({199,99,1,1});verify({0,99,200,1});verify({199,0,1,100});
    for(int i=0;i<500;++i){int x=rng.uniform(0,200),y=rng.uniform(0,100);verify({x,y,rng.uniform(1,201-x),rng.uniform(1,101-y)});}
    bool rejected=false;try{rectangle_sum(p,{-1,0,1,1});}catch(const std::runtime_error&){rejected=true;}check(rejected,"negative ROI accepted");
    rejected=false;try{rectangle_sum(p,{0,0,0,1});}catch(const std::runtime_error&){rejected=true;}check(rejected,"empty ROI accepted");
    // OpenCV积分图采用额外一行一列、CV_64F作独立交叉检验。
    cv::Mat official;cv::integral(image,official,CV_64F);check(official.rows==101&&official.cols==201,"padded dimensions");
    check(official.at<double>(100,200)==rectangle_sum(p,{0,0,200,100}),"official integral mismatch");
    std::cout<<"PASS: "<<passed<<" rectangles, 2 invalid ROIs, OpenCV cross-check\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 2;}}
