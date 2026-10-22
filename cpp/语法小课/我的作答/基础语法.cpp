// 【本题说明开始】
// C++分组练习：基础语法
//
// 题目与要求：
// ・程序、输出与换行：在lesson_output中输出自己的学习主题和一道加法，分两行显示。
// ・表达式、语句与代码块：在lesson_output中把“先算、再存、再输出”写成三步，加一条说明目的的注
// 释。
// ・变量、常量与类型：在lesson_variables中用变量表示3行4列，输出总格数；再改成5列。
// ・类型：能存什么、能做什么：在lesson_variables给数量、价格、是否有效、等级、名称各选一种类型，
// 并解释选择。
// ・初始化、赋值与常量：在lesson_variables分别标注初始化与后续赋值，把固定步长设为const。
// ・读取输入与检查失败：在lesson_input中从cin读取两个整数；成功输出和，失败输出input error。
// ・算术、转换与比较：在lesson_numbers中同时输出整数商和浮点商；给除数0单独的拒绝分支。
// ・库、头文件、命名空间与接口：在lesson_output调用std::max，显式包含<algorithm>；写下注释区分
// 头文件、函数名和命名空间。
//
// 写在哪里：只编辑本文件中的自己的实现；不要复制参考答案覆盖。
// 怎么做：先手算样例，再写实现，最后检查正常、边界和错误情况。
// 怎么检查：按当前主题的正常/边界结果自检；运行成功不等于完成所有小课。
//
// 本文件按题目选择相关函数/代码块，不要求一次完成所有主题。
// 没有统一stdin/stdout或自动全文件判分，网页选择题/填空不是C++运行检查。
// 运行先输入菜单号：1输出/表达式/头文件；2变量/类型/初始化；3输入检查；4算术。
// 完整题目与文本格式：../README.md。
// 【本题说明结束】
//
#include <iostream>

// 与网页小课对应；只填本组TODO，不需要一次完成全部。

// 第1题：程序、输出与换行
// 在lesson_output中输出自己的学习主题和一道加法，分两行显示。
void lesson_output() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 1\n";
}

// 第2题：变量、常量与类型
// 在lesson_variables中用变量表示3行4列，输出总格数；再改成5列。
void lesson_variables() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 2\n";
}

// 第3题：读取输入与检查失败
// 在lesson_input中从cin读取两个整数；成功输出和，失败输出input error。
void lesson_input() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 3\n";
}

// 第4题：算术、转换与比较
// 在lesson_numbers中同时输出整数商和浮点商；给除数0单独的拒绝分支。
void lesson_numbers() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 4\n";
}

int main() {
    std::cout << "Choose exercise 1-4: ";
    int choice = 0;
    if (!(std::cin >> choice)) return 1;
    switch (choice) {
    case 1: lesson_output(); break;
    case 2: lesson_variables(); break;
    case 3: lesson_input(); break;
    case 4: lesson_numbers(); break;
    default: std::cout << "Choose 1-4\n"; return 1;
    }
}
