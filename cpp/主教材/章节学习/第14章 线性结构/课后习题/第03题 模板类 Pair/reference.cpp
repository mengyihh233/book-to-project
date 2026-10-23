#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
class Pair {
public:
    Pair(T first, T second) : first_(first), second_(second) {}
    T first() const { return first_; }
    T second() const { return second_; }
    std::string toString() const {
        std::ostringstream out;
        out << '(' << first_ << ", " << second_ << ')';
        return out.str();
    }

private:
    T first_;
    T second_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间");
        }
        /* BEGIN 1 */
        std::vector<std::string> firsts(n), seconds(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> firsts[i] >> seconds[i])) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行不完整");
        }
        
        bool allInt = true;
        for (int i = 0; i < n && allInt; ++i) {
            for (const std::string* text : {&firsts[i], &seconds[i]}) {
                std::size_t used = 0;
                try {
                    std::stoll(*text, &used);
                } catch (const std::exception&) {
                    allInt = false;
                    break;
                }
                if (used != text->size()) allInt = false;
            }
        }
        
        if (allInt) {
            std::vector<Pair<long long>> pairs;
            for (int i = 0; i < n; ++i) {
                pairs.emplace_back(std::stoll(firsts[i]), std::stoll(seconds[i]));
            }
            std::sort(pairs.begin(), pairs.end(), [](const Pair<long long>& a, const Pair<long long>& b) {
                return a.first() != b.first() ? a.first() < b.first() : a.second() < b.second();
            });
            for (const auto& p : pairs) std::cout << p.toString() << '\n';
        } else {
            bool anyNumber = false;
            for (int i = 0; i < n; ++i) {
                for (const std::string* text : {&firsts[i], &seconds[i]}) {
                    std::size_t used = 0;
                    try {
                        std::stoll(*text, &used);
                        if (used == text->size()) anyNumber = true;
                    } catch (const std::exception&) {
                    }
                }
            }
            if (anyNumber) throw std::invalid_argument("同一组输入里不能混用数字和字符串");
            std::vector<Pair<std::string>> pairs;
            for (int i = 0; i < n; ++i) pairs.emplace_back(firsts[i], seconds[i]);
            std::sort(pairs.begin(), pairs.end(), [](const Pair<std::string>& a, const Pair<std::string>& b) {
                return a.first() != b.first() ? a.first() < b.first() : a.second() < b.second();
            });
            for (const auto& p : pairs) std::cout << p.toString() << '\n';
        }
        /* END 1 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
