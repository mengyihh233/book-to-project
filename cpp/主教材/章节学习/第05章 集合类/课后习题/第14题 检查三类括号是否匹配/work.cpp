// 【本题说明开始】
// 第5章习题14：检查三类括号是否匹配
//
// 题目：输入恰好一行文本（最多100000字节），只检查()、[]、{}，其他字节忽略。输出true或false。空文本行匹配；完全缺失输入属于格式错误。
// 实现什么：bool bracketsMatch(const std::string& text)
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
bool bracketsMatch(const std::string& text);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try{
        std::string line,extra;
        if(!book_input::logicalLine(std::cin,line)||line.size()>100000)throw std::invalid_argument("missing or large string");
        if(book_input::logicalLine(std::cin,extra)||std::cin.bad())throw std::invalid_argument("extra input");
        std::cout<<(bracketsMatch(line)?"true":"false")<<'\n';
    }catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

bool bracketsMatch(const std::string& text) {
    /* BEGIN 1：bracketsMatch */
    // 提示：遇左括号入栈，遇右括号检查栈顶是否配对，结束时栈必须为空。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
