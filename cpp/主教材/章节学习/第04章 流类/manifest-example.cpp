// 独立编写的整合示例：输入流来自manifest-input.txt，不打开图像。
#include "课后习题/第06题/lesson.h"
int main() {
    std::string line;unsigned long long row=0;
    std::ostringstream report;
    while(std::getline(std::cin,line)) {
        ++row;
        std::istringstream in(line);in.imbue(std::locale::classic());
        std::string path;int width=0,height=0;double exposure=0;
        if(!(in>>path>>width>>height>>exposure) || width<=0 || height<=0 || !std::isfinite(exposure) || exposure<=0) {
            std::cerr<<"Invalid record at line "<<row<<'\n';return 2;
        }
        in>>std::ws;
        if(!in.eof()) {std::cerr<<"Extra data at line "<<row<<'\n';return 2;}
        report<<defaultExtension(path,"*.txt")<<' '<<width<<'x'<<height<<' '
              <<std::fixed<<std::setprecision(3)<<exposure<<"ms\n";
    }
    if(std::cin.bad()) return 2;
    std::cout<<report.str();
}
