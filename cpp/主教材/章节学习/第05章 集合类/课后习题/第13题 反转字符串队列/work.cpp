// 【本题说明开始】
// 第5章习题13：反转字符串队列
//
// 题目：首行n（0..10000），随后恰好n行字符串，可为空、含中文或首尾空格。输出n，再输出反转后的n行；队首到队尾为输入/输出顺序。
// 实现什么：void reverseQueue(std::queue<std::string>& values)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/vector_lesson.h"
#include <stack>
#include <queue>

// 本题要实现的接口（声明已给出）。
void reverseQueue(std::queue<std::string>& values);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try{
        std::string line;
        if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing count");
        int n=strictNumber<int>(line);
        if(n<0||n>10000)throw std::out_of_range("count");
        std::queue<std::string> values;
        for(int i=0;i<n;++i){
            if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing string");
            values.push(line);
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad())throw std::invalid_argument("extra input");
        reverseQueue(values);
        std::cout<<n<<'\n';
        while(!values.empty()){
            std::cout<<values.front()<<'\n';
            values.pop();
        }
    }catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void reverseQueue(std::queue<std::string>& values) {
    /* BEGIN 1：reverseQueue */
    // 提示：借助辅助容器把顺序倒过来；注意输出前先打印元素个数。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
