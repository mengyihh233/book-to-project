# 第14章 项目：括号匹配 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：括号匹配
// 用栈检查三种括号是否配对，同时记录最大嵌套深度。
#include <iostream>
#include <string>

namespace {

char matchOf(char open) {
    if (open == '(') return ')';
    if (open == '[') return ']';
    return '}';
}

bool isOpen(char c) { return c == '(' || c == '[' || c == '{'; }
bool isClose(char c) { return c == ')' || c == ']' || c == '}'; }

}  // namespace

int main() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "缺少输入\n";
        return 2;
    }
    if (!line.empty() && line.back() == '\r') line.pop_back();

    std::string stack;          // 用 string 当栈，push_back / pop_back
    int depth = 0;
    for (char c : line) {
        if (c == ' ' || c == '\t') continue;
        if (isOpen(c)) {
            stack.push_back(c);
            if (static_cast<int>(stack.size()) > depth) depth = static_cast<int>(stack.size());
        } else if (isClose(c)) {
            if (stack.empty() || matchOf(stack.back()) != c) {
                std::cout << "匹配 否\n深度 0\n";
                return 0;
            }
            stack.pop_back();
        } else {
            std::cerr << "出现非法字符：" << c << "\n";
            return 2;
        }
    }
    if (!stack.empty()) {
        std::cout << "匹配 否\n深度 0\n";
        return 0;
    }
    std::cout << "匹配 是\n深度 " << depth << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `([]{})` → 匹配 是，深度 **2**
- [ ] `((()))` → 匹配 是，深度 **3**
- [ ] `()` → 匹配 是，深度 1
- [ ] `([)]` → 匹配 否，深度 0
- [ ] `(]` → 匹配 否
- [ ] 空行 → 匹配 是，深度 **0**
- [ ] `a(` → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
