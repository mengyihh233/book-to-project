// 【本题说明开始】
// 第5章习题12：用栈逆序输出整数
//
// 题目：每行一个int32整数，0结束且不参与输出；最多10000个非零记录。读完后每行输出一个逆序整数。必须有0终止，终止后不得有额外行。
// 实现什么：void reverseIntegers(std::istream& in, std::ostream& out)
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
void reverseIntegers(std::istream& in, std::ostream& out);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try{
        reverseIntegers(std::cin,std::cout);
    }catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void reverseIntegers(std::istream& in, std::ostream& out) {
    /* BEGIN 1：reverseIntegers */
    // 提示：读一个压一个，遇到 0 停止；再不断弹出，每弹一个输出一行。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
