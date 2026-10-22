#include <iostream>

// 配套原创参考：先完成“我的作答/基础语法.cpp”，再核对本文件。
void lesson_output() {
    std::cout << "C++ learning\n";
    std::cout << "2 + 3 = " << 2 + 3 << '\n';
}

void lesson_variables() {
    const int rows = 3;
    int columns = 4;
    std::cout << rows * columns << '\n';
    columns = 5;
    std::cout << rows * columns << '\n';
}

void lesson_input() {
    int a = 0, b = 0;
    if (!(std::cin >> a >> b)) {
        std::cout << "input error\n";
        return;
    }
    // 先提升类型，避免两个合法int相加时发生int溢出。
    std::cout << static_cast<long long>(a) + b << '\n';
}

void lesson_numbers() {
    int a = 0, b = 0;
    if (!(std::cin >> a >> b)) {
        std::cout << "input error\n";
        return;
    }
    if (b == 0) {
        std::cout << "division by zero\n";
        return;
    }
    // 整数商向0截断；提升可避免INT_MIN / -1的int溢出。
    std::cout << static_cast<long long>(a) / b << ' '
              << static_cast<double>(a) / b << '\n';
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
