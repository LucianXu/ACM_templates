# 基环树

```cpp
// ring detection (directed) //
vi vis(n + 1), fa(n + 1), ring;
auto dfs = [&](auto&& self, int u) -> bool {
    vis[u] = 1;
    for (const auto& v : e[u]) {
        if (!vis[v]) {
            fa[v] = u;
            if (self(self, v)) {
                return true;
            }
        } else if (vis[v] == 1) {
            ring.push_back(v);
            for (auto x = u; x != v; x = fa[x]) {
                ring.push_back(x);
            }
            reverse(all(ring));
            return true;
        }
    }
    vis[u] = 2;
    return false;
};
for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
        if (dfs(dfs, i)) {
            // operations //
        }
    }
}
```

```cpp
// cycle detection (undirected) //
vi vis(n + 1), ring;
vpi fa(n + 1);
auto dfs = [&](auto&& self, int u, int from) -> bool {
    vis[u] = 1;
    for (const auto& [v, id] : e[u]) {
        if (id == from) continue;
        if (!vis[v]) {
            fa[v] = {u, id};
            if (self(self, v, id)) {
                return true;
            }
        } else if (vis[v] == 1) {
            ring.push_back(v);
            for (auto x = u; x != v; x = fa[x].ff) {
                ring.push_back(x);
            }
            return true;
        }
    }
    vis[u] = 2;
    return false;
};
for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
        if (dfs(dfs, i, 0)) {
            // operations //
        }
    }
}
```

