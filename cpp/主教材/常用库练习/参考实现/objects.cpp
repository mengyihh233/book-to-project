// 阅读注释｜第6章类设计与第12章内存主题；以下为中文概括和适配观察点。
// 构造维护状态，const查询不改对象；move转交所有权，不再解引用移走的指针。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

class Point {
    double x_;
    double y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }
    Point operator+(const Point& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }
};

void ownershipCalls() {
    const Point original(1, 2);
    const auto sum = original + Point(3, 4);
    assert(sum.x() == 4 && sum.y() == 6);
    assert(original.x() == 1 && original.y() == 2);
    auto owner = std::make_unique<int>(7);
    auto newOwner = std::move(owner);
    assert(!owner && *newOwner == 7);
    // Never dereference the moved-from owner or delete newOwner.get().
    std::cout << "objects: const interface, value result and move ownership OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { ownershipCalls(); return 0; }
#endif
