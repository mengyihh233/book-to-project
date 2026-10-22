// 阅读注释｜第20章迭代策略，PDF610起；以下为中文概括和适配观察点。
// 算法依赖迭代器与比较前提；unique/remove_if返回逻辑尾，随后erase才改变大小。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

template<class Iterator, class Predicate>
int countMatching(Iterator first, Iterator last, Predicate predicate) {
    int count = 0;
    for (; first != last; ++first) if (predicate(*first)) ++count;
    return count;
}

void algorithmCalls() {
    std::vector<int> values{3, 1, 3, 2, 1};
    std::sort(values.begin(), values.end());
    assert((values == std::vector<int>{1, 1, 2, 3, 3}));
    const auto newEnd = std::unique(values.begin(), values.end());
    assert(values.size() == 5); // unique alone does not resize the vector.
    values.erase(newEnd, values.end());
    assert((values == std::vector<int>{1, 2, 3}));
    assert(std::binary_search(values.begin(), values.end(), 2));
    assert(std::lower_bound(values.begin(), values.end(), 2) == values.begin() + 1);
    assert(std::upper_bound(values.begin(), values.end(), 2) == values.begin() + 2);
    assert(std::find(values.begin(), values.end(), 9) == values.end());
    assert(std::count(values.begin(), values.end(), 2) == 1);
    assert(std::accumulate(values.begin(), values.end(), 0) == 6);
    std::transform(values.begin(), values.end(), values.begin(), [](int x) { return x * x; });
    assert((values == std::vector<int>{1, 4, 9}));
    const auto keepEnd = std::remove_if(values.begin(), values.end(), [](int x) { return x > 4; });
    values.erase(keepEnd, values.end());
    assert((values == std::vector<int>{1, 4}));
    const auto even = [](int x) { return x % 2 == 0; };
    assert(countMatching(values.begin(), values.end(), even) == 1);
    const std::list<int> linked{2, 3, 4};
    assert(countMatching(linked.begin(), linked.end(), even) == 2);
    assert(countMatching(linked.end(), linked.end(), even) == 0);
    std::cout << "algorithms: ordered lookup, logical ends and callbacks OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { algorithmCalls(); return 0; }
#endif
