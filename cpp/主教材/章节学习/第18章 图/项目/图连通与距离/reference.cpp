// 参考实现：图连通与距离
// 无向图：先按最小顶点升序输出每个连通分量，再从 0 号顶点做 BFS 输出最短边数。
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n = 0, m = 0;
    if (!(std::cin >> n >> m) || n < 1 || n > 100000) {
        std::cerr << "顶点数必须在 1 到 100000 之间\n";
        return 2;
    }
    if (m < 0 || m > 200000) {
        std::cerr << "边数必须在 0 到 200000 之间\n";
        return 2;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        if (!(std::cin >> u >> v)) {
            std::cerr << "第 " << i + 1 << " 条边不完整\n";
            return 2;
        }
        if (u < 0 || u >= n || v < 0 || v >= n) {
            std::cerr << "边的端点越界：" << u << " " << v << "\n";
            return 2;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);   // 无向边，两个方向都存
    }

    std::vector<char> seen(n, 0);
    std::vector<std::vector<int>> comps;
    for (int s = 0; s < n; ++s) {
        if (seen[s]) continue;
        std::vector<int> comp;
        std::queue<int> q;
        q.push(s);
        seen[s] = 1;
        while (!q.empty()) {
            const int cur = q.front();
            q.pop();
            comp.push_back(cur);
            for (int nxt : adj[cur]) {
                if (!seen[nxt]) {
                    seen[nxt] = 1;
                    q.push(nxt);
                }
            }
        }
        std::sort(comp.begin(), comp.end());   // 分量内按顶点升序
        comps.push_back(comp);
    }
    // 起点从 0 往上扫，分量天然按最小顶点升序，无需再排。

    std::cout << "分量数 " << comps.size() << "\n";
    for (const auto& comp : comps) {
        for (std::size_t i = 0; i < comp.size(); ++i) {
            if (i) std::cout << ' ';
            std::cout << comp[i];
        }
        std::cout << "\n";
    }

    std::vector<int> dist(n, -1);
    std::queue<int> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        const int cur = q.front();
        q.pop();
        for (int nxt : adj[cur]) {
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }

    std::cout << "距离";
    for (int i = 0; i < n; ++i) std::cout << ' ' << dist[i];
    std::cout << "\n";
    return 0;
}
