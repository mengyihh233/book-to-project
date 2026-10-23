// 【本题说明开始】
// 第16章 · 习题1：家谱树的读入与缩进显示
//
// 题目：把一个「孩子:父亲」的名单建成一棵树，再按辈分逐层缩进打印出来。
// 实现什么：`readFamilyTree()` 建树 + `displayFamilyTree()` 先序缩进显示。
// 写在哪里：只补下方 BEGIN 1（建树）与 BEGIN 2（递归显示）之间的代码。
// 文本格式：按辈分缩进输出；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct FamilyTreeNode {
    std::string name;
    std::vector<FamilyTreeNode*> children;
    explicit FamilyTreeNode(const std::string& who) : name(who) {}
};

// 去掉首尾空白。
std::string trim(const std::string& text) {
    std::size_t first = 0;
    while (first < text.size() && std::isspace(static_cast<unsigned char>(text[first]))) ++first;
    std::size_t last = text.size();
    while (last > first && std::isspace(static_cast<unsigned char>(text[last - 1]))) --last;
    return text.substr(first, last - first);
}

// 后序释放整棵树。
void freeTree(FamilyTreeNode* node) {
    if (node == nullptr) return;
    for (FamilyTreeNode* child : node->children) freeTree(child);
    delete node;
}

// 两个函数都已声明：实现写在下面的补写区里（整段函数定义都由你写）。
FamilyTreeNode* readFamilyTree();
void displayFamilyTree(FamilyTreeNode* tree);

/* BEGIN 1 */
// 读根节点那一行，再逐行读「孩子:父亲」，把结点挂到父亲下面，最后 return 树根。
// @@1@@
/* END 1 */

/* BEGIN 2 */
// 先序递归：输出「深度×2 个空格 + 名字」，再对每个孩子递归。
// @@2@@
/* END 2 */

int main() {
    try {
        FamilyTreeNode* root = readFamilyTree();
        displayFamilyTree(root);
        freeTree(root);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
