// 阅读注释｜第5章集合类主题，PDF148起；以下为中文概括和适配观察点。
// 本组使用标准容器作教学适配；按操作选择结构，不把接口调用冒充原始库内部实现。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

void containerCalls() {
    std::vector<int> samples;
    samples.reserve(8);
    assert(samples.empty() && samples.size() == 0 && samples.capacity() >= 8);
    for (int value : {3, 1, 3}) samples.push_back(value);
    samples.at(1) = 2;
    assert(samples.front() == 3 && samples.back() == 3);
    samples.insert(samples.begin() + 1, 9);
    samples.erase(samples.begin() + 1);
    samples.pop_back();
    assert((samples == std::vector<int>{3, 2}));
    samples.resize(4, 0);
    assert((samples == std::vector<int>{3, 2, 0, 0}));
    samples.clear();
    assert(samples.empty());
    // No front/back/pop on an empty container; no use of invalidated iterators.

    std::stack<int> history;
    std::queue<int> pending;
    for (int value : {10, 20}) { history.push(value); pending.push(value); }
    assert(history.top() == 20 && pending.front() == 10 && pending.back() == 20);
    history.pop(); pending.pop();
    assert(history.top() == 10 && pending.front() == 20);
    assert(history.size() == 1 && pending.size() == 1);

    std::map<std::string, int> frequency;
    for (const std::string word : {"red", "blue", "red"}) ++frequency[word];
    const auto before = frequency.size();
    assert(frequency.find("missing") == frequency.end());
    assert(frequency.size() == before);
    assert(frequency["red"] == 2);
    (void)frequency["missing"];
    assert(frequency.size() == before + 1);
    assert(frequency.erase("missing") == 1 && frequency.erase("missing") == 0);
    std::set<int> labels{2, 1, 2};
    assert(labels.size() == 2 && labels.count(2) == 1);
    assert(!labels.insert(2).second && labels.insert(3).second);
    assert(labels.erase(9) == 0);
    std::cout << "containers: vector, stack, queue, map and set OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { containerCalls(); return 0; }
#endif
