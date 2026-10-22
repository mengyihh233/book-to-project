#include "random_tools.h"
#include <iomanip>
int main() {
    try {
        const auto count = readUnsigned(1000000);
        const auto seed = readUnsigned(4294967295ULL); requireEnd();
        if (count == 0) throw std::invalid_argument("count must be positive");
        std::mt19937 engine(seed);
        double sum = 0;
        for (std::uint32_t i = 0; i < count; ++i) sum += unitReal(engine);
        std::cout << std::fixed << std::setprecision(10) << sum / count << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n"; return 2;
    }
}
