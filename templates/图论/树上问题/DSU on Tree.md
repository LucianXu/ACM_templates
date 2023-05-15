# DSU on Tree

给出一课 $n$ 个节点以 $1$ 为根的树，每个节点染上一种颜色，询问以 $u$ 为节点的子树中有多少种颜色。

```cpp
// Problem: U41492 树上数颜色

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, dfn = 0, cnttot = 0;
    std::cin >> n;
    vvi e(n + 1);
    vi siz(n + 1), col(n + 1), son(n + 1), dfnl(n + 1), dfnr(n + 1), rank(n + 1);
    vi ans(n + 1), cnt(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> col[i];
    }
    auto add = [&](int u) -> void {
        if (cnt[col[u]] == 0) cnttot++;
        cnt[col[u]]++;
    };
    auto del = [&](int u) -> void {
        cnt[col[u]]--;
        if (cnt[col[u]] == 0) cnttot--;
    };
    auto dfs1 = [&](auto&& self, int u, int fa) -> void {
        dfnl[u] = ++dfn;
        rank[dfn] = u;
        siz[u] = 1;
        for (auto v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            siz[u] += siz[v];
            if (!son[u] or siz[son[u]] < siz[v]) son[u] = v;
        }
        dfnr[u] = dfn;
    };
    auto dfs2 = [&](auto&& self, int u, int fa, bool op) -> void {
        for (auto v : e[u]) {
            if (v == fa or v == son[u]) continue;
            self(self, v, u, false);
        }
        if (son[u]) self(self, son[u], u, true);
        for (auto v : e[u]) {
            if (v == fa or v == son[u]) continue;
            rep(i, dfnl[v], dfnr[v]) { add(rank[i]); }
        }
        add(u);
        ans[u] = cnttot;
        if (op == false) {
            rep(i, dfnl[u], dfnr[u]) { del(rank[i]); }
        }
    };
    dfs1(dfs1, 1, 0);
    dfs2(dfs2, 1, 0, false);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        int u;
        std::cin >> u;
        std::cout << ans[u] << endl;
    }
    return 0;
}
```

