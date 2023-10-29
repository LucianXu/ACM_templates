# LCA

## 倍增算法

```cpp
// LCA //
vvi e(n + 1), fa(n + 1, vi(50));
vi dep(n + 1);

auto dfs = [&](auto&& self, int u) -> void {
    for (auto v : e[u]) {
        if (v == fa[u][0]) continue;
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        self(self, v);
    }
};

auto init = [&]() -> void {
    dep[root] = 1;
    dfs(dfs, root);
    for (int j = 1; j <= 30; j++) {
        for (int i = 1; i <= n; i++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
};
init();

auto LCA = [&](int a, int b) -> int {
    if (dep[a] > dep[b]) std::swap(a, b);
    int d = dep[b] - dep[a];
    for (int i = 0; (1 << i) <= d; i++) {
        if (d & (1 << i)) b = fa[b][i];
    }
    if (a == b) return a;
    for (int i = 30; i >= 0 and a != b; i--) {
        if (fa[a][i] == fa[b][i]) continue;
        a = fa[a][i];
        b = fa[b][i];
    }
    return fa[a][0];
};

auto dist = [&](int a, int b) -> int { return dep[a] + dep[b] - dep[LCA(a, b)] * 2; };
```

