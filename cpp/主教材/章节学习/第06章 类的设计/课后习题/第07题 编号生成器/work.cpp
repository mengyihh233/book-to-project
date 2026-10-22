// 【本题说明开始】
// 第6章 · 习题7：编号生成器
//
// 题目：按行读入「前缀 个数」，为每个前缀连续生成编号，同一前缀跨行接着数。
// 实现什么：`LabelGenerator::next()`（按前缀分别计数）+ `main` 的读入与输出。
// 写在哪里：只补下方 BEGIN 1（LabelGenerator::next）与 BEGIN 2（读入与连续输出）之间的代码。
// 文本格式：每个标签一行「前缀+编号」，同前缀跨行累加；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

// 编号生成器：同一个前缀共用一个计数器，编号从 0 开始，跨调用接着往下数。
class LabelGenerator {
public:
    std::string next(const std::string& prefix) {
        /* BEGIN 1 */
        // counters_ 里存每个前缀「下一个要用的编号」。
        // 返回 prefix + 编号（不补零），然后把计数器加一。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
    }

private:
    std::map<std::string, int> counters_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }

        /* BEGIN 2 */
        // 1) 把 n 行全部读进 vector<pair<string,int>>；
        // 2) 全部校验（前缀 1..20 字符、个数 1..1000），有任何一行不合法就抛
        //    std::invalid_argument —— 不要边读边打印，否则非法输入会吐出半份结果；
        // 3) 校验通过后再按顺序调用 next() 输出，每得到一个标签输出一行。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
