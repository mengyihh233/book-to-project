# 第16章 · 习题1：家谱树的读入与缩进显示 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 「父亲一定在前面」是这个格式的全部便利：一边读一边就能把结点挂上去，不用两遍扫描。
- 需要一个 `map<string, FamilyTreeNode*>` 从名字反查结点——树只能从根往下走，反查必须靠表。
- 孩子按读入顺序 `push_back`，显示时才会和输入顺序一致；这里**不能**排序。
- 缩进就是递归参数 `depth` 每次 +2，`std::string(depth, ' ')` 一行搞定。

## 容易错的边界

- 名字里有空格（`William I`），所以每行必须整行读入再按**第一个**冒号切，不能 `cin >>`。
- 孩子名重复（同一人写两次）要报错，否则树里会出现两个同名结点。
- 空行是允许的，但 `:A`（孩子名为空）和 `Bob`（没有冒号）都不合法。
- 出错时直接抛异常退出，已经 new 出来的结点留给进程回收，不用为异常路径写清理代码。

## 参考实现

```cpp
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
```
