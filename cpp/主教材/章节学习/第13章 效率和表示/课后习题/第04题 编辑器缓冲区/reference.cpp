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
