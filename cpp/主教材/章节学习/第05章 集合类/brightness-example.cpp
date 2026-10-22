// 不依赖OpenCV：先用ASCII灰度数据验证统计与分箱。
#include "课后习题/第02题/lesson.h"
#include "课后习题/第03题/lesson.h"
#include "课后习题/第04题/lesson.h"
int main() {
    try {
        std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int n=strictNumber<int>(line);
        if(n<1||n>10000) throw std::out_of_range("pixel count");
        std::vector<double> intensities;std::vector<int> percentages;
        for(int i=0;i<n;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing pixel");
            int x=strictNumber<int>(line);
            if(x<0||x>255) throw std::out_of_range("pixel outside 0..255");
            intensities.push_back(x);
            percentages.push_back((x*100+127)/255);
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra data");
        auto counts=histogram(percentages);std::ostringstream out;
        out<<"pixels "<<n<<'\n'<<std::fixed<<std::setprecision(3)
           <<"mean "<<mean(intensities)<<'\n'<<"stddev "<<stddev(intensities)<<'\n';
        for(int i=0;i<11;++i) out<<(i==10?"100":std::to_string(i*10)+"s")<<' '<<counts[i]<<'\n';
        std::cout<<out.str();
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 2;}
}
