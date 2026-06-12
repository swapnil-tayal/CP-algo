// https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/?envType=daily-question&envId=2026-06-12

class LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    void dfs(int node, int par) {
        up[node][0] = par;

        for (int j = 1; j < LOG; j++) {
            if (up[node][j - 1] != -1)
                up[node][j] = up[up[node][j - 1]][j - 1];
            else
                up[node][j] = -1;
        }

        for (auto child : adj[node]) {
            if (child == par) continue;

            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }

public:
    LCA(int N, vector<vector<int>>& edges, int root = 0) {
        n = N;
        LOG = 1;

        while ((1 << LOG) <= n) LOG++;

        adj.resize(n);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, -1));

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(root, -1);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = LOG - 1; j >= 0; j--) {
            if (diff & (1 << j))
                u = up[u][j];
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }
};
