#include "random_tools.h"
#include <iomanip>
int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL); requireEnd();
        std::mt19937 engine(seed);
        int atoms = 10000;
        std::cout << "0 " << atoms << '\n';
        for (int year = 1; atoms > 0; ++year) {
            if (year > 1000) throw std::runtime_error("simulation limit reached");
            int survivors = 0;
            for (int i = 0; i < atoms; ++i) if (!halfEvent(engine)) ++survivors;
            atoms = survivors;
            std::cout << year << ' ' << atoms << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n"; return 2;
    }
}
