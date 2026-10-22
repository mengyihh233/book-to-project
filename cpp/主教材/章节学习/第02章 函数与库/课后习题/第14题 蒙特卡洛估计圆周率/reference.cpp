#include "random_tools.h"
#include <iomanip>
int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL); requireEnd();
        std::mt19937 engine(seed);
        constexpr int trials = 10000;
        int inside = 0;
        for (int i = 0; i < trials; ++i) {
            const double x = 2 * unitReal(engine) - 1;
            const double y = 2 * unitReal(engine) - 1;
            if (x * x + y * y < 1) ++inside;
        }
        std::cout << inside << ' ' << std::fixed << std::setprecision(4)
                  << 4.0 * inside / trials << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n"; return 2;
    }
}
