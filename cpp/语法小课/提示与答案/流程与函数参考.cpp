#include <iostream>

// 普通函数定义在其他函数外；值通过return返回。
double square(double x) {
    return x * x;
}

void swapValues(int& a, int& b) {
    const int oldA = a;
    a = b;
    b = oldA;
}

void lesson_conditions() {
    int score = 0;
    if (!(std::cin >> score)) {
        std::cout << "input error\n";
        return;
    }
    std::cout << (score >= 0 && score <= 100 ? "valid\n" : "invalid\n");
}

void lesson_loops() {
    int n = 0;
    if (!(std::cin >> n)) {
        std::cout << "input error\n";
        return;
    }
    // 与第1章核心任务约定一致：0 <= n <= 10000。
    if (n < 0 || n > 10000) {
        std::cout << "out of range\n";
        return;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) sum += i;
    std::cout << sum << '\n';
}

void lesson_functions() {
    std::cout << square(0) << '\n';
    std::cout << square(-3) << '\n';
    std::cout << square(2.5) << '\n';
}

void lesson_references() {
    int a = 0, b = 0;
    if (!(std::cin >> a >> b)) {
        std::cout << "input error\n";
        return;
    }
    swapValues(a, b);
    std::cout << a << ' ' << b << '\n';
    // 改成值传递再测试：函数内部的交换不再改变这里的a和b。
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
