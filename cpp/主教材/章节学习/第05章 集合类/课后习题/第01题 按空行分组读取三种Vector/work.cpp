// 【本题说明开始】
// 第5章 · 习题1：按空行分组读取三种Vector
//
// 题目：输入第1行int/double/string，第2行调用readVector的次数1..20，后续每行一个元素，真正的空行分组。每次调用替换旧容器，空组或EOF得到空容器；EOF后再次
//   调用仍为空。字符串记录保留前后空格，只有长度0才结束该组；数值行须整行合法。每次输出容器长度一行，随后每个元素一行，double用17位有效数字。完成约定调用后若还有任何行则拒绝。
// 实现什么：template<class T> void readBlock(std::istream& in, std::vector<T>& values)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/vector_lesson.h"

// 本题要实现的函数（模板定义要放在使用它的重载之前）。
template<class T> void readBlock(std::istream& in, std::vector<T>& values) {
    /* BEGIN 1：读取一个空行分隔的块 */
    // 提示：循环读整行，读到空行就结束这一组；每行都要检查长度与 ASCII。
    // 数值类型用 strictNumber<T>(line) 转换，string 直接原样存入。
    // 先读进临时容器，再整体赋给 values —— 不要边读边改传入的容器。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// 给定的三个重载：按元素类型分派到上面的模板，不要改。
inline void readVector(std::istream& in, std::vector<int>& data) { readBlock(in, data); }
inline void readVector(std::istream& in, std::vector<double>& data) { readBlock(in, data); }
inline void readVector(std::istream& in, std::vector<std::string>& data) { readBlock(in, data); }

// 给定的输出函数：每组先打元素个数，再逐个打元素。
template<class T> void displayBlocks(std::istream& in, std::ostream& out, int calls) {
    std::vector<T> data;
    for (int k = 0; k < calls; ++k) {
        readVector(in, data);
        out << data.size() << '\n';
        for (const auto& item : data) out << std::setprecision(17) << item << '\n';
    }
}

// 给定的主程序：读类型与次数、按类型分派、最后检查多余输入。不要重写。
int main() {
    std::string type, line, extra;
    if (!book_input::logicalLine(std::cin, type) || !book_input::logicalLine(std::cin, line)) return 2;
    try {
        int calls = strictNumber<int>(line);
        if (calls < 1 || calls > 20) throw std::out_of_range("calls must be 1..20");
        std::ostringstream out;
        out.imbue(std::locale::classic());
        if (type == "int") displayBlocks<int>(std::cin, out, calls);
        else if (type == "double") displayBlocks<double>(std::cin, out, calls);
        else if (type == "string") displayBlocks<std::string>(std::cin, out, calls);
        else throw std::invalid_argument("unknown type");
        if (book_input::logicalLine(std::cin, extra)) throw std::invalid_argument("extra input after blocks");
        std::cout << out.str();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
