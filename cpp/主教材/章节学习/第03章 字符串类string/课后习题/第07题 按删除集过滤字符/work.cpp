// 【本题说明开始】
// 第3章习题7：按删除集过滤字符
//
// 题目：输入两行：原字符串、删除字符集。返回删除这些字符后的新字符串，保持剩余顺序。大小写敏感、重复删除字符不改变结果，原字符串不修改。
// 实现什么：removeCharacters(const std::string& str, const std::string& remove)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "input.h"
#include <string>
#include <algorithm>
#include <stdexcept>

// 本题要实现的接口（声明已给出）。
std::string removeCharacters(const std::string& str, const std::string& remove);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto str=line(),remove=line();
        endInput();
        std::cout << removeCharacters(str,remove) << "\n";
    } catch(const std::exception& error) {
        std::cerr<<error.what()<<"\n";
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::string removeCharacters(const std::string& str, const std::string& remove) {
    /* BEGIN 1：removeCharacters */
    // 提示：遍历原串，字符不在删除集里就追加到结果；原串保持不变。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
