// 【本题说明开始】
// 第19章 · 习题3：抽象图形与最上层命中
//
// 题目：用抽象基类 + 纯虚函数管住三种图形，再对查询点找出「最上层」那个命中的图形。
// 实现什么：`Rect/Circle/Triangle` 的 `contains` + `main` 里的最上层命中循环。
// 写在哪里：只补下方 BEGIN 1（三个子类的纯虚实现）与 BEGIN 2（从后往前找最上层命中）之间的代码。
// 文本格式：每个点一行命中结果；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 抽象基类：三个纯虚接口靠子类实现，外部只认 Shape*。
class Shape {
public:
    virtual ~Shape() {}
    virtual std::string name() const = 0;
    virtual bool contains(double px, double py) const = 0;
};

class Rect : public Shape {
public:
    Rect(double x, double y, double w, double h) : x_(x), y_(y), w_(w), h_(h) {}
    std::string name() const override { return "rect"; }
    bool contains(double px, double py) const override;

private:
    double x_;
    double y_;
    double w_;
    double h_;
};

class Circle : public Shape {
public:
    Circle(double cx, double cy, double r) : cx_(cx), cy_(cy), r_(r) {}
    std::string name() const override { return "circle"; }
    bool contains(double px, double py) const override;

private:
    double cx_;
    double cy_;
    double r_;
};

class Triangle : public Shape {
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3) {}
    std::string name() const override { return "tri"; }
    bool contains(double px, double py) const override;

private:
    double x1_, y1_, x2_, y2_, x3_, y3_;
};

/* BEGIN 1 */
// 三个子类的 contains：边界都算命中。
// @@1@@
/* END 1 */

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("图形个数必须在 1 到 1000 之间");
        }

        std::vector<Shape*> shapes;
        for (int i = 0; i < n; ++i) {
            std::string kind;
            if (!(std::cin >> kind)) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 个图形缺少类型");
            if (kind == "rect") {
                double x = 0, y = 0, w = 0, h = 0;
                if (!(std::cin >> x >> y >> w >> h)) throw std::invalid_argument("矩形参数不完整");
                if (w <= 0 || h <= 0) throw std::invalid_argument("矩形的宽高必须大于 0");
                shapes.push_back(new Rect(x, y, w, h));
            } else if (kind == "circle") {
                double cx = 0, cy = 0, r = 0;
                if (!(std::cin >> cx >> cy >> r)) throw std::invalid_argument("圆的参数不完整");
                if (r <= 0) throw std::invalid_argument("圆的半径必须大于 0");
                shapes.push_back(new Circle(cx, cy, r));
            } else if (kind == "tri") {
                double x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
                if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) throw std::invalid_argument("三角形参数不完整");
                const double area2 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
                if (area2 == 0) throw std::invalid_argument("三点共线，不构成三角形");
                shapes.push_back(new Triangle(x1, y1, x2, y2, x3, y3));
            } else {
                throw std::invalid_argument("未知图形类型：" + kind);
            }
        }

        /* BEGIN 2 */
        // 读 m 与 m 个点；每个点从后往前找第一个 contains 的图形并输出。
        // @@2@@
        /* END 2 */

        for (Shape* shape : shapes) delete shape;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
