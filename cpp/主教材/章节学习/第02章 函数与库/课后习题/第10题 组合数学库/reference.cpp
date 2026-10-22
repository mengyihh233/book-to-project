#include "combinatorics.h"
#include <exception>
#include <iostream>
#include <stdexcept>
int main() {
    try {
        char operation;
        long long n, k;
        if (!(std::cin >> operation >> n >> k)) throw std::runtime_error("use P/C n k");
        std::cin >> std::ws;
        if (!std::cin.eof()) throw std::runtime_error("unexpected input");
        if (operation == 'P') std::cout << combinatorics::permutations(n, k) << '\n';
        else if (operation == 'C') std::cout << combinatorics::combinations(n, k) << '\n';
        else throw std::runtime_error("operation must be P or C");
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
