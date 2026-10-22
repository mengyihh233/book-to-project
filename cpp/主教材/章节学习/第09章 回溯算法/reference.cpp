// 阅读注释｜原书第9章，PDF279起；以下为中文概括与自编配套观察点。
// 概念：回溯在每一层选择、递归探索，并恢复调用者的局部状态。
// 看代码：本例按元素位置选择取或不取；push之后对应pop，结果按位置区分，重复数值可能产生相同数值序列。
// 先预测：如果忘记pop，后一个分支会继承哪部分错误状态？
// 本程序不是原书同号答案或全章覆盖证明；assert核对不要用-DNDEBUG关闭。
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using Solutions = std::vector<std::vector<int>>;

void explore(const std::vector<int>& values, std::size_t i, int target,
             int sum, std::vector<int>& path, Solutions& answers) {
    if (i == values.size()) {
        if (sum == target) answers.push_back(path);
        return;
    }
    explore(values, i + 1, target, sum, path, answers);
    path.push_back(values[i]);
    explore(values, i + 1, target, sum + values[i], path, answers);
    path.pop_back();  // Restore the caller's path before trying another branch.
}

Solutions subsetsWithSum(const std::vector<int>& values, int target) {
    if (values.size() > 16 || target < -1000 || target > 1000)
        throw std::invalid_argument("input outside teaching limits");
    for (int value : values)
        if (value < -1000 || value > 1000)
            throw std::invalid_argument("element outside teaching limits");
    Solutions answers;
    std::vector<int> path;
    explore(values, 0, target, 0, path, answers);
    return answers;
}

int main() {
    const auto answers = subsetsWithSum({1, 2, 3}, 3);
    assert(answers.size() == 2);
    assert(subsetsWithSum({}, 0).size() == 1);
    assert(subsetsWithSum({}, 1).empty());
    assert(subsetsWithSum({2, -1, 1}, 1).size() == 2);
    assert(subsetsWithSum({1, 1}, 1).size() == 2); // Distinct indices.
    for (const auto& answer : answers) {
        for (int value : answer) std::cout << value << ' ';
        std::cout << '\n';
    }
    return 0;
}
