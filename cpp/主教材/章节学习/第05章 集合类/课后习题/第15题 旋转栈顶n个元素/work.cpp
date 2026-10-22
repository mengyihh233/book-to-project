// 【本题说明开始】
// 第5章习题15：旋转栈顶n个元素
//
// 题目：第一行是ASCII可打印字符（最多10000字节），从栈底写到栈顶，空格也占一个元素。第二行n k，均非负，n不能超过栈大小，k不超过int64最大值。只旋转栈顶n个，使原栈顶元素向栈
//   底方向循环移动k次。n=0定义为空操作。输出旋转后栈底到栈顶的整行。
// 实现什么：void roll(std::stack<char>& values, int n, long long k)
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
void roll(std::stack<char>& values, int n, long long k);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try{
        std::string text,line,extra;
        if(!book_input::logicalLine(std::cin,text)||text.size()>10000)throw std::invalid_argument("missing or large stack");
        for(unsigned char c:text)if(c<32||c>126)throw std::invalid_argument("ASCII stack required");
        if(!book_input::logicalLine(std::cin,line))throw std::invalid_argument("missing roll parameters");
        std::istringstream parameters(line);
        int n;
        long long k;
        if(!(parameters>>n>>k))throw std::invalid_argument("invalid roll parameters");
        parameters>>std::ws;
        if(!parameters.eof()||book_input::logicalLine(std::cin,extra)||std::cin.bad())throw std::invalid_argument("extra input");
        std::stack<char> values;
        for(char c:text)values.push(c);
        roll(values,n,k);
        std::string result(values.size(),' ');
        for(std::size_t i=result.size();i>0;--i){
            result[i-1]=values.top();
            values.pop();
        }
        std::cout<<result<<'\n';
    }catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void roll(std::stack<char>& values, int n, long long k) {
    /* BEGIN 1：roll */
    // 提示：先把栈顶 n 个元素取出，按 k % n 找到切点，再按顺序放回。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
