# 第19章 项目：薪资多态报表 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：薪资多态报表
// 基类 Employee 提供虚函数 pay()/kind()，三种雇员各自实现，统一按多态结算。
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

const long long kMaxMoney = 1000000000LL;   // 分
const long long kMaxHours = 1000;

class Employee {
public:
    explicit Employee(std::string name) : name_(std::move(name)) {}
    virtual ~Employee() = default;

    virtual char kind() const = 0;              // 'S' / 'H' / 'C'
    virtual long long pay() const = 0;          // 应发，单位：分
    const std::string& name() const { return name_; }

protected:
    std::string name_;
};

class Salaried : public Employee {
public:
    Salaried(std::string name, long long monthly)
        : Employee(std::move(name)), monthly_(monthly) {}
    char kind() const override { return 'S'; }
    long long pay() const override { return monthly_; }

private:
    long long monthly_;
};

class Hourly : public Employee {
public:
    Hourly(std::string name, long long rate, long long hours)
        : Employee(std::move(name)), rate_(rate), hours_(hours) {}
    char kind() const override { return 'H'; }
    // 前 160 小时按原价；超出部分 1.5 倍，整除向下取整。
    long long pay() const override {
        const long long normal = std::min<long long>(hours_, 160);
        const long long overtime = hours_ > 160 ? hours_ - 160 : 0;
        return rate_ * normal + rate_ * 3 * overtime / 2;
    }

private:
    long long rate_;
    long long hours_;
};

class Commissioned : public Employee {
public:
    Commissioned(std::string name, long long base, long long sales, long long percent)
        : Employee(std::move(name)), base_(base), sales_(sales), percent_(percent) {}
    char kind() const override { return 'C'; }
    long long pay() const override { return base_ + sales_ * percent_ / 100; }

private:
    long long base_;
    long long sales_;
    long long percent_;
};

// 分 -> 元，固定两位小数。
void print_money(long long cents) {
    std::cout << cents / 100 << '.';
    const long long fen = cents % 100;
    if (fen < 10) std::cout << '0';
    std::cout << fen;
}

bool money_ok(long long v) { return v >= 0 && v <= kMaxMoney; }

int main() {
    int k = 0;
    if (!(std::cin >> k) || k < 1 || k > 100000) {
        std::cerr << "员工人数必须在 1 到 100000 之间\n";
        return 2;
    }

    std::vector<std::unique_ptr<Employee>> staff;
    staff.reserve(static_cast<std::size_t>(k));
    for (int i = 0; i < k; ++i) {
        std::string type, name;
        if (!(std::cin >> type >> name)) {
            std::cerr << "第 " << i + 1 << " 条记录不完整\n";
            return 2;
        }
        if (type == "S") {
            long long monthly = 0;
            if (!(std::cin >> monthly) || !money_ok(monthly)) {
                std::cerr << name << " 的月薪不合法\n";
                return 2;
            }
            staff.push_back(std::make_unique<Salaried>(name, monthly));
        } else if (type == "H") {
            long long rate = 0, hours = 0;
            if (!(std::cin >> rate >> hours) || !money_ok(rate)) {
                std::cerr << name << " 的时薪不合法\n";
                return 2;
            }
            if (hours < 0 || hours > kMaxHours) {
                std::cerr << name << " 的工时必须在 0 到 1000 之间\n";
                return 2;
            }
            staff.push_back(std::make_unique<Hourly>(name, rate, hours));
        } else if (type == "C") {
            long long base = 0, sales = 0, percent = 0;
            if (!(std::cin >> base >> sales >> percent)) {
                std::cerr << name << " 的记录不完整\n";
                return 2;
            }
            if (!money_ok(base) || !money_ok(sales)) {
                std::cerr << name << " 的底薪或销售额不合法\n";
                return 2;
            }
            if (percent < 0 || percent > 100) {
                std::cerr << name << " 的提成百分比必须在 0 到 100 之间\n";
                return 2;
            }
            staff.push_back(std::make_unique<Commissioned>(name, base, sales, percent));
        } else {
            std::cerr << "未知的雇员类型：" << type << "\n";
            return 2;
        }
    }

    long long total = 0;
    for (const auto& e : staff) {
        const long long p = e->pay();
        std::cout << e->name() << ' ' << e->kind() << ' ';
        print_money(p);
        std::cout << "\n";
        total += p;
    }
    std::cout << "合计 ";
    print_money(total);
    std::cout << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] 上面那组输入 → 三行 + `合计 21650.00`
- [ ] `1` + `C dan 100 250 5` → `dan C 1.12`（250 × 5 ÷ 100 = 12，不是 12.5）
- [ ] `1` + `H eve 100 161` → `eve H 161.50`（多 1 小时按 150 分算）
- [ ] `2` + `S zed 0` 和 `H zero 0 0` → 两行 `0.00`，合计 `0.00`
- [ ] 类型写成 `X` → 返回 2，屏幕无输出
- [ ] 月薪 `-1` → 返回 2，屏幕无输出
- [ ] 人数 `0` → 返回 2，屏幕无输出

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
