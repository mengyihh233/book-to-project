# 第13章 · 习题4：编辑器缓冲区 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 光标是一个 `0..len` 的下标，插在 `cursor` 位置、删的是 `cursor-1`。
- `forward` 到末尾就停，`backward` 到开头就停，`delete` 在开头什么都不做。
- `print` 是把 `|` **插进去**再输出，不要改动真实文本。

## 容易错的边界

- 删除时先判断 `cursor > 0`，否则会删到 `string::npos` 那位。
- 插入后光标必须右移，否则连续插入会变成逆序。
- 空缓冲区 `print` 要输出 `|`，不是空行。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class EditorBuffer {
public:
    void insert(char ch);
    void forward();
    void backward();
    void deleteCharacter();
    int length() const { return static_cast<int>(text_.size()); }
    std::string text() const { return text_; }
    int cursor() const { return cursor_; }

private:
    std::string text_;
    int cursor_ = 0;
};

/* BEGIN 1 */
void EditorBuffer::insert(char ch) {
    text_.insert(text_.begin() + cursor_, ch);
    ++cursor_;
}

void EditorBuffer::forward() {
    if (cursor_ < static_cast<int>(text_.size())) ++cursor_;
}

void EditorBuffer::backward() {
    if (cursor_ > 0) --cursor_;
}

void EditorBuffer::deleteCharacter() {
    if (cursor_ > 0) {
        text_.erase(text_.begin() + (cursor_ - 1));
        --cursor_;
    }
}
/* END 1 */

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 200) {
            throw std::invalid_argument("命令条数必须在 0 到 200 之间");
        }
        EditorBuffer buffer;

        /* BEGIN 2 */
        for (int i = 0; i < n; ++i) {
            std::string command;
            if (!(std::cin >> command)) throw std::invalid_argument("命令不完整");
            if (command == "insert") {
                std::string ch;
                if (!(std::cin >> ch) || ch.size() != 1) throw std::invalid_argument("insert 需要一个字符");
                buffer.insert(ch[0]);
            } else if (command == "forward") {
                buffer.forward();
            } else if (command == "backward") {
                buffer.backward();
            } else if (command == "delete") {
                buffer.deleteCharacter();
            } else if (command == "length") {
                std::cout << buffer.length() << '\n';
            } else if (command == "print") {
                const std::string text = buffer.text();
                std::cout << text.substr(0, buffer.cursor()) << '|'
                          << text.substr(buffer.cursor()) << '\n';
            } else {
                throw std::invalid_argument("未知命令：" + command);
            }
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
