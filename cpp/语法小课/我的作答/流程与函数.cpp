// 【本题说明开始】
// C++分组练习：流程与函数
//
// 题目与要求：
// ・条件、逻辑与边界：在lesson_conditions中判断分数是否在0到100内，检查-1、0、100、101。
// ・循环、累加与停止：在lesson_loops中求1到n之和，检查n=0、1、4；再回第1章核心练习。
// ・函数、返回值与作用域：在文件中单独定义普通square函数，在lesson_functions里调用它，测试0、
// -3、2.5。
// ・函数接口：形参、实参与返回值：在文件外层定义twice，在lesson_functions调用；写出输入、返回
// 值、是否修改调用方。
// ・值传递、引用与const：在lesson_references中用引用交换两个整数，再改为值传递观察差异。
// ・重载与默认参数：让调用清楚：在流程与函数文件外层增加int与double两个add版本；在
// lesson_functions比较默认参数、显式参数和double调用。
// ・模板与类型要求：在已有流程与函数.cpp中，单独定义larger函数模板，再在lesson_functions里增加
// 两次调用；不需要另建项目。
//
// 写在哪里：只编辑本文件中的自己的实现；不要复制参考答案覆盖。
// 怎么做：先手算样例，再写实现，最后检查正常、边界和错误情况。
// 怎么检查：按当前主题的正常/边界结果自检；运行成功不等于完成所有小课。
//
// 本文件按题目选择相关函数/代码块，不要求一次完成所有主题。
// 没有统一stdin/stdout或自动全文件判分，网页选择题/填空不是C++运行检查。
// 运行先输入菜单号：1条件；2循环；3函数/接口/重载；4引用。函数定义放在其他函数外。
// 完整题目与文本格式：../README.md。
// 【本题说明结束】
//
#include <iostream>

// 与网页小课对应；只填本组TODO，不需要一次完成全部。

// 第1题：条件、逻辑与边界
// 在lesson_conditions中判断分数是否在0到100内，检查-1、0、100、101。
void lesson_conditions() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 1\n";
}

// 第2题：循环、累加与停止
// 在lesson_loops中求1到n之和，检查n=0、1、4；再回第1章核心练习。
void lesson_loops() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 2\n";
}

// 第3题：函数、返回值与作用域
// 在文件中单独定义square函数，在lesson_functions里调用它，测试0、-3、2.5。
void lesson_functions() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 3\n";
}

// 第4题：值传递、引用与const
// 在lesson_references中用引用交换两个整数，再改为值传递观察差异。
void lesson_references() {
    // TODO：在这里编写自己的代码。
    std::cout << "TODO 4\n";
}

int main() {
    std::cout << "Choose exercise 1-4: ";
    int choice = 0;
    if (!(std::cin >> choice)) return 1;
    switch (choice) {
    case 1: lesson_conditions(); break;
    case 2: lesson_loops(); break;
    case 3: lesson_functions(); break;
    case 4: lesson_references(); break;
    default: std::cout << "Choose 1-4\n"; return 1;
    }
}
