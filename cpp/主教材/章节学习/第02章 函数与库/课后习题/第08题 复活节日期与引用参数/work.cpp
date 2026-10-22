// 【本题说明开始】
// 第2章习题8：复活节日期与引用参数
//
// 题目：- reference.cpp：原书范围的参考入口；easter.h：带中文注释的参考函数。
// 实现什么：void findEaster(int year, std::string& month, int& day)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <stdexcept>
#include <string>

// month、day 通过引用把两个结果交给 main；void 表示没有单独的返回值。
void findEaster(int year, std::string& month, int& day) {
    /* BEGIN 1：按原题算法，通过引用写回月份与日期 */
    // 只接受1700..1899年，超出范围应抛出异常。
    // 算法说明在README第4段；月份写"March"或"April"，日期写入day。
    // 直接修改引用参数，不要再声明同名的局部month、day。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// 给定：读取且仅接受一个整数年份、调用函数、输出并处理异常。
int main() {
    try {
        int year;
        std::string extra;
        if (!(std::cin >> year) || (std::cin >> extra))
            throw std::invalid_argument("expected one integer year");
        std::string month;
        int day = 0;
        findEaster(year, month, day);
        std::cout << month << ' ' << day << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
