#include <cstddef>
#include <deque>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct Graph {
    std::vector<std::string> names;                 // 下标 -> 名字
    std::map<std::string, int> index;               // 名字 -> 下标
    std::vector<std::vector<int>> adj;              // 邻接表，按边的读入顺序
};

// 递归 DFS（给好，作为对照）。
void dfsVisit(const Graph& g, int node, std::vector<bool>& seen, std::vector<int>& order) {
    seen[static_cast<std::size_t>(node)] = true;
    order.push_back(node);
    for (int next : g.adj[static_cast<std::size_t>(node)]) {
        if (!seen[static_cast<std::size_t>(next)]) dfsVisit(g, next, seen, order);
    }
}

std::vector<int> recursiveDfs(const Graph& g, int start) {
    std::vector<bool> seen(g.names.size(), false);
    std::vector<int> order;
    dfsVisit(g, start, seen, order);
    return order;
}

// 把顺序打印成 `标签 = A B C`。
void printOrder(const std::string& label, const std::vector<int>& order, const Graph& g) {
    std::cout << label << " =";
    for (int node : order) std::cout << ' ' << g.names[static_cast<std::size_t>(node)];
    std::cout << '\n';
}

std::vector<int> stackDfs(const Graph& g, int start);
std::vector<int> bfsOrder(const Graph& g, int start);

std::vector<int> stackDfs(const Graph& g, int start) {
    /* BEGIN 1 */
    // 用显式栈：弹出栈顶、已访问就跳过、否则访问并把邻接点按顺序压栈。
    std::vector<int> order;
    std::vector<bool> seen(g.names.size(), false);
    std::vector<int> stack;
    stack.push_back(start);
    
    while (!stack.empty()) {
        const int node = stack.back();
        stack.pop_back();
        if (seen[static_cast<std::size_t>(node)]) continue;
    
        seen[static_cast<std::size_t>(node)] = true;
        order.push_back(node);
        for (int next : g.adj[static_cast<std::size_t>(node)]) {
            stack.push_back(next);
        }
    }
    return order;
    /* END 1 */
}

std::vector<int> bfsOrder(const Graph& g, int start) {
    /* BEGIN 2 */
    // 用队列：出队访问，未访问的邻接点「入队时就标记」。
    std::vector<int> order;
    std::vector<bool> seen(g.names.size(), false);
    std::deque<int> queue;
    queue.push_back(start);
    seen[static_cast<std::size_t>(start)] = true;
    
    while (!queue.empty()) {
        const int node = queue.front();
        queue.pop_front();
        order.push_back(node);
        for (int next : g.adj[static_cast<std::size_t>(node)]) {
            if (seen[static_cast<std::size_t>(next)]) continue;
            seen[static_cast<std::size_t>(next)] = true;
            queue.push_back(next);
        }
    }
    return order;
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        int m = 0;
        if (!(std::cin >> n >> m) || n < 1 || n > 1000 || m < 0 || m > 100000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间，m 在 0 到 100000 之间");
        }

        Graph g;
        g.adj.resize(static_cast<std::size_t>(n));
        for (int i = 0; i < n; ++i) {
            std::string name;
            if (!(std::cin >> name)) throw std::invalid_argument("节点名个数不足");
            if (g.index.count(name) > 0) throw std::invalid_argument("节点重名：" + name);
            g.index[name] = i;
            g.names.push_back(name);
        }

        for (int i = 0; i < m; ++i) {
            std::string u;
            std::string v;
            if (!(std::cin >> u >> v)) throw std::invalid_argument("边数不足");
            const auto from = g.index.find(u);
            const auto to = g.index.find(v);
            if (from == g.index.end() || to == g.index.end()) {
                throw std::invalid_argument("边引用了不存在的节点：" + u + " " + v);
            }
            g.adj[static_cast<std::size_t>(from->second)].push_back(to->second);
            g.adj[static_cast<std::size_t>(to->second)].push_back(from->second);
        }

        std::string startName;
        if (!(std::cin >> startName) || g.index.find(startName) == g.index.end()) {
            throw std::invalid_argument("起点不在节点表里");
        }
        const int startIndex = g.index.find(startName)->second;

        printOrder("递归 DFS", recursiveDfs(g, startIndex), g);
        printOrder("栈版 DFS", stackDfs(g, startIndex), g);
        printOrder("BFS", bfsOrder(g, startIndex), g);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
