// 零件轮廓计数。标准输入为UTF-8 JSON请求，标准输出为简短结果。
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
namespace fs=std::filesystem;
static void require(bool ok,const char* text){if(!ok)throw std::runtime_error(text);}
static void save_image(const fs::path&p,const cv::Mat&image){
    std::vector<uchar>bytes;require(cv::imencode(".png",image,bytes),"PNG encode failed");
    std::ofstream f(p,std::ios::binary);f.write(reinterpret_cast<const char*>(bytes.data()),static_cast<std::streamsize>(bytes.size()));f.close();require(bool(f),"image write failed");
}
static double numeric(const cv::FileStorage&cfg,const char*key,double fallback){
    auto node=cfg[key];if(node.empty())return fallback;
    require(node.isInt()||node.isReal(),"numeric setting required");double value=double(node);require(std::isfinite(value),"finite setting required");return value;
}
int main(){
    try{
        std::string text;char c;
        while(std::cin.get(c)){require(text.size()<65536,"request too large");text+=c;}
        cv::FileStorage cfg(text,cv::FileStorage::READ|cv::FileStorage::MEMORY|cv::FileStorage::FORMAT_JSON);
        require(cfg.isOpened(),"invalid request JSON");
        std::string input,output;require(cfg["input"].isString()&&cfg["output"].isString(),"input/output strings required");cfg["input"]>>input;cfg["output"]>>output;require(!input.empty()&&!output.empty(),"empty path");
        const double threshold=numeric(cfg,"threshold",100),minimum=numeric(cfg,"min_area",200),maximum=numeric(cfg,"max_area",100000),invert=numeric(cfg,"invert",1);
        require(threshold>=0&&threshold<=255&&threshold==std::floor(threshold),"threshold must be integer 0..255");
        require(minimum>=0&&minimum<=maximum,"invalid area range");require(invert==0||invert==1,"invert must be 0 or 1");
        const auto in=fs::u8path(input),out=fs::u8path(output);
        require(fs::is_regular_file(in),"input is not a regular file");require(!fs::exists(out),"output already exists; choose a new directory");
        require(fs::file_size(in)>0&&fs::file_size(in)<=64*1024*1024,"compressed input limit: 64 MiB");
        std::ifstream f(in,std::ios::binary);require(bool(f),"cannot read input");std::vector<uchar>bytes((std::istreambuf_iterator<char>(f)),{});
        cv::Mat src=cv::imdecode(bytes,cv::IMREAD_COLOR);require(!src.empty(),"image decode failed");require(src.total()<=25000000,"decoded image exceeds 25M pixels");
        cv::Mat gray,mask;cv::cvtColor(src,gray,cv::COLOR_BGR2GRAY);cv::threshold(gray,mask,threshold,255,invert?cv::THRESH_BINARY_INV:cv::THRESH_BINARY);
        std::vector<std::vector<cv::Point>>contours;cv::findContours(mask.clone(),contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
        struct Object{double area;cv::Rect box;cv::Point2d center;};std::vector<Object>objects;
        for(const auto&contour:contours){double area=cv::contourArea(contour);if(area<=0||area<minimum||area>maximum)continue;auto m=cv::moments(contour);if(m.m00==0)continue;objects.push_back({area,cv::boundingRect(contour),{m.m10/m.m00,m.m01/m.m00}});}
        std::sort(objects.begin(),objects.end(),[](const Object&a,const Object&b){return a.box.x!=b.box.x?a.box.x<b.box.x:a.box.y<b.box.y;});
        cv::Mat overlay=src.clone();for(std::size_t i=0;i<objects.size();++i){const auto&o=objects[i];cv::rectangle(overlay,o.box,{30,160,30},2);cv::putText(overlay,std::to_string(i+1),o.box.tl()+cv::Point(0,-5),cv::FONT_HERSHEY_SIMPLEX,.6,{0,0,220},2);}
        // 输入与参数校验、检测均成功后才建立输出目录；不提供覆盖操作。
        require(fs::create_directories(out),"cannot create fresh output directory");
        save_image(out/"mask.png",mask);save_image(out/"overlay.png",overlay);
        cv::FileStorage report(".json",cv::FileStorage::WRITE|cv::FileStorage::MEMORY|cv::FileStorage::FORMAT_JSON);
        report<<"width"<<src.cols<<"height"<<src.rows<<"count"<<int(objects.size())<<"threshold"<<threshold<<"min_area"<<minimum<<"max_area"<<maximum<<"invert"<<invert;
        report<<"objects"<<"[";for(std::size_t i=0;i<objects.size();++i){const auto&o=objects[i];report<<"{"<<"id"<<int(i+1)<<"area"<<o.area<<"x"<<o.box.x<<"y"<<o.box.y<<"width"<<o.box.width<<"height"<<o.box.height<<"cx"<<o.center.x<<"cy"<<o.center.y<<"}";}report<<"]";
        const auto json=report.releaseAndGetString();std::ofstream target(out/"report.json",std::ios::binary);target<<json;target.close();require(bool(target),"report write failed");
        std::cout<<"count="<<objects.size()<<"\n";return 0;
    }catch(const std::exception&e){std::cerr<<"inspection failed: "<<e.what()<<'\n';return 2;}
}
