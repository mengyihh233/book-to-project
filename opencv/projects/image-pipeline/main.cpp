// 综合练习：读取图片、验证参数、提取边缘，并用Unicode安全的文件流保存PNG。
#define NOMINMAX
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif
namespace fs=std::filesystem;
std::vector<std::string> arguments(int argc,char**argv){
#ifdef _WIN32
    (void)argc;(void)argv;
    int count=0;
    struct WideArguments{LPWSTR* p;~WideArguments(){if(p)LocalFree(p);}};
    WideArguments block{CommandLineToArgvW(GetCommandLineW(),&count)};
    if(!block.p)throw std::runtime_error("无法读取命令行参数");
    std::vector<std::string> result;
    for(int i=0;i<count;++i){
        int n=WideCharToMultiByte(CP_UTF8,0,block.p[i],-1,nullptr,0,nullptr,nullptr);
        if(n<=0)throw std::runtime_error("参数编码转换失败");
        std::string text(n,'\0');
        WideCharToMultiByte(CP_UTF8,0,block.p[i],-1,text.data(),n,nullptr,nullptr);
        text.pop_back();result.push_back(text);
    }
    return result;
#else
    return {argv,argv+argc};
#endif
}
int integer(const std::string&text){
    size_t used=0;int value=std::stoi(text,&used);
    if(used!=text.size())throw std::runtime_error("参数必须是完整整数");
    return value;
}
int main(int argc,char**argv){
    try{
        auto args=arguments(argc,argv);
        std::string input,output;int low=50,high=120,blur=5;bool overwrite=false;
        for(size_t i=1;i<args.size();++i){
            const std::string&key=args[i];
            if(key=="--help"){
                std::cout<<"用法：--input 图片 --output 结果.png [--low 50 --high 120 --blur 5] [--overwrite]\n";
                return 0;
            }
            if(key=="--overwrite"){overwrite=true;continue;}
            if(key!="--input"&&key!="--output"&&key!="--low"&&key!="--high"&&key!="--blur")throw std::runtime_error("未知参数");
            if(++i>=args.size())throw std::runtime_error("参数缺少取值");
            if(key=="--input")input=args[i];else if(key=="--output")output=args[i];
            else if(key=="--low")low=integer(args[i]);else if(key=="--high")high=integer(args[i]);else blur=integer(args[i]);
        }
        if(input.empty()||output.empty())throw std::runtime_error("必须指定输入和输出路径");
        if(low<0||high>255||low>high)throw std::runtime_error("阈值须满足0<=low<=high<=255");
        if(blur<1||blur>31||blur%2==0)throw std::runtime_error("高斯核必须是1到31的奇数");
        fs::path in=fs::u8path(input),out=fs::u8path(output);
        if(!fs::is_regular_file(in))throw std::runtime_error("输入不是普通文件");
        if(fs::exists(out)&&fs::equivalent(in,out))throw std::runtime_error("输出不能与输入指向同一文件");
        if(fs::exists(out)&&!overwrite)throw std::runtime_error("输出已存在；确认需要覆盖时加--overwrite");
        if(out.extension()!=L".png")throw std::runtime_error("本练习仅输出小写.png扩展名");
        auto size=fs::file_size(in);
        if(size==0||size>64*1024*1024)throw std::runtime_error("输入文件为空或超过64MiB教学限制");
        std::ifstream stream(in,std::ios::binary);
        if(!stream)throw std::runtime_error("无法打开输入文件");
        std::vector<uchar> bytes((std::istreambuf_iterator<char>(stream)),{});
        cv::Mat source=cv::imdecode(bytes,cv::IMREAD_COLOR);
        if(source.empty())throw std::runtime_error("输入无法解码为图片");
        cv::Mat gray,smooth,edges;
        cv::cvtColor(source,gray,cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray,smooth,{blur,blur},1.2);
        cv::Canny(smooth,edges,low,high);
        std::vector<uchar> encoded;
        if(!cv::imencode(".png",edges,encoded))throw std::runtime_error("PNG编码失败");
        if(!out.parent_path().empty())fs::create_directories(out.parent_path());
        std::ofstream target(out,std::ios::binary);
        target.write(reinterpret_cast<const char*>(encoded.data()),static_cast<std::streamsize>(encoded.size()));
        target.close();if(!target)throw std::runtime_error("结果写入失败");
        std::cout<<"处理完成："<<source.cols<<"x"<<source.rows<<"，边缘像素="<<cv::countNonZero(edges)
                 <<"，low="<<low<<"，high="<<high<<"，blur="<<blur<<"\n";
        return 0;
    }catch(const std::exception&e){std::cerr<<"处理失败："<<e.what()<<"\n";return 2;}
}
