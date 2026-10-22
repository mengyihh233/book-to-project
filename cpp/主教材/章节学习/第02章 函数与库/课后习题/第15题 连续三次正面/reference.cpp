#include "random_tools.h"
#include <iomanip>
int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL); requireEnd();
        std::mt19937 engine(seed);
        int streak = 0;
        int flips = 0;
        while (streak < 3) {
            if (flips == 1000000) throw std::runtime_error("simulation limit reached");
            const bool heads = halfEvent(engine);
            ++flips;
            streak = heads ? streak + 1 : 0;
            std::cout << (heads ? "HEADS" : "TAILS") << '\n';
        }
        std::cout << "TOTAL " << flips << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n"; return 2;
    }
}
