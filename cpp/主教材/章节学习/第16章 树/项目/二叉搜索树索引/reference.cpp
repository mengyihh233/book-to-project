// 参考实现：二叉搜索树索引
// 依次插入（重复值忽略），报告高度/结点数/前序/中序，再按查询报深度。
#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left;
    Node* right;
    explicit Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

// 插入：小的往左、大的往右，相等直接返回（重复值不新建结点）。
Node* insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

int height(const Node* root) {
    if (root == nullptr) return 0;
    const int l = height(root->left);
    const int r = height(root->right);
    return 1 + (l > r ? l : r);
}

int count_nodes(const Node* root) {
    if (root == nullptr) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void preorder(const Node* root) {
    if (root == nullptr) return;
    std::cout << ' ' << root->value;
    preorder(root->left);
    preorder(root->right);
}

void inorder(const Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    std::cout << ' ' << root->value;
    inorder(root->right);
}

// 找到返回深度（根为 1），找不到返回 0。
int depth_of(const Node* root, int value) {
    int depth = 1;
    const Node* cur = root;
    while (cur != nullptr) {
        if (value == cur->value) return depth;
        cur = (value < cur->value) ? cur->left : cur->right;
        ++depth;
    }
    return 0;
}

void destroy(Node* root) {
    if (root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 100000) {
        std::cerr << "结点个数必须在 0 到 100000 之间\n";
        return 2;
    }
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) {
            std::cerr << "第 " << i + 1 << " 个值读取失败\n";
            destroy(root);
            return 2;
        }
        root = insert(root, value);
    }

    int m = 0;
    if (!(std::cin >> m) || m < 0 || m > 100000) {
        std::cerr << "查询个数必须在 0 到 100000 之间\n";
        destroy(root);
        return 2;
    }
    // 先把查询读完再输出：输入不完整时不要吐半份报表。
    std::vector<int> queries(static_cast<std::size_t>(m));
    for (int i = 0; i < m; ++i) {
        if (!(std::cin >> queries[static_cast<std::size_t>(i)])) {
            std::cerr << "第 " << i + 1 << " 个查询读取失败\n";
            destroy(root);
            return 2;
        }
    }

    std::cout << "高度 " << height(root) << "\n";
    std::cout << "结点 " << count_nodes(root) << "\n";
    std::cout << "前序";
    preorder(root);
    std::cout << "\n";
    std::cout << "中序";
    inorder(root);
    std::cout << "\n";

    for (int i = 0; i < m; ++i) {
        const int value = queries[static_cast<std::size_t>(i)];
        const int d = depth_of(root, value);
        if (d == 0) {
            std::cout << "未找到 " << value << "\n";
        } else {
            std::cout << "深度 " << value << " " << d << "\n";
        }
    }

    destroy(root);
    return 0;
}
