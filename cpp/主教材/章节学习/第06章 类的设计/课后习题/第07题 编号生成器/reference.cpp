#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

class LabelGenerator {
public:
    std::string next(const std::string& prefix) {
        int& counter = counters_[prefix];
        return prefix + std::to_string(counter++);
    }

private:
    std::map<std::string, int> counters_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::vector<std::pair<std::string, int>> requests;
        for (int i = 0; i < n; ++i) {
            std::string prefix;
            int count = 0;
            if (!(std::cin >> prefix >> count)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行不完整");
            }
            if (prefix.empty() || prefix.size() > 20) {
                throw std::invalid_argument("前缀长度必须在 1 到 20 之间");
            }
            if (count < 1 || count > 1000) {
                throw std::invalid_argument("每行个数必须在 1 到 1000 之间");
            }
            requests.emplace_back(prefix, count);
        }

        LabelGenerator generator;
        for (const auto& request : requests) {
            for (int k = 0; k < request.second; ++k) {
                std::cout << generator.next(request.first) << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
