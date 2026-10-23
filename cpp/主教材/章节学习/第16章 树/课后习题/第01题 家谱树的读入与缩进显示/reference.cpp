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
FamilyTreeNode* readFamilyTree() {
std::string line;
if (!std::getline(std::cin, line)) {
    throw std::invalid_argument("缺少根节点那一行");
}
const std::string root = trim(line);
if (root.empty()) throw std::invalid_argument("根节点名字是空的");

FamilyTreeNode* tree = new FamilyTreeNode(root);
std::map<std::string, FamilyTreeNode*> index;
index[root] = tree;

while (std::getline(std::cin, line)) {
    const std::string text = trim(line);
    if (text.empty()) continue;

    const std::size_t colon = text.find(':');
    if (colon == std::string::npos) {
        throw std::invalid_argument("这一行没有冒号：" + text);
    }
    const std::string child = trim(text.substr(0, colon));
    const std::string parent = trim(text.substr(colon + 1));
    if (child.empty()) throw std::invalid_argument("孩子名字是空的：" + text);

    const auto where = index.find(parent);
    if (where == index.end()) {
        throw std::invalid_argument("父亲还没出现过：" + parent);
    }
    if (index.count(child) > 0) {
        throw std::invalid_argument("这个名字出现了两次：" + child);
    }

    FamilyTreeNode* node = new FamilyTreeNode(child);
    where->second->children.push_back(node);
    index[child] = node;
}
return tree;
}
/* END 1 */

/* BEGIN 2 */
// 先序递归：输出「深度×2 个空格 + 名字」，再对每个孩子递归。
namespace {

void displayHelper(FamilyTreeNode* node, int depth) {
    std::cout << std::string(static_cast<std::size_t>(depth), ' ') << node->name << '\n';
    for (FamilyTreeNode* child : node->children) {
        displayHelper(child, depth + 2);
    }
}

}  // namespace

void displayFamilyTree(FamilyTreeNode* tree) {
    if (tree == nullptr) return;
    displayHelper(tree, 0);
}
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
