# 树链剖分

## 重链剖分 HLD

对一棵有根树进行如下 $4$ 种操作：

1. $1 \ x \ y \ z$：将节点 $x$ 到节点 $y$ 的最短路径上所有节点的值加上 $z$。
2. $2 \ x \ y$：查询节点 $x$ 到节点 $y$ 的最短路径上所有节点的值的和。
3. $3 \ x \ z$：将以节点 $x$ 为根的子树上所有节点的值加上 $z$。
4. $4 \ x$：查询以节点 $x$ 为根的子树上所有节点的值的和。

```cpp
// HLD //
int cnt = 0;
vi son(n + 1), fa(n + 1), siz(n + 1), depth(n + 1);
vi dfn(n + 1), rank(n + 1), top(n + 1), botton(n + 1);

auto dfs1 = [&](auto&& self, int u) -> void {
    son[u] = -1, siz[u] = 1;
    for (auto v : e[u]) {
        if (depth[v] != 0) continue;
        depth[v] = depth[u] + 1;
        fa[v] = u;
        self(self, v);
        siz[u] += siz[v];
        if (son[u] == -1 or siz[v] > siz[son[u]]) son[u] = v;
    }
};

auto dfs2 = [&](auto&& self, int u, int t) -> void {
    top[u] = t;
    dfn[u] = ++cnt;
    rank[cnt] = u;
    botton[u] = dfn[u];
    if (son[u] == -1) return;
    self(self, son[u], t);
    Max(botton[u], botton[son[u]]);
    for (auto v : e[u]) {
        if (v != son[u] and v != fa[u]) {
            self(self, v, v);
            Max(botton[u], botton[v]);
        }
    }
};

depth[root] = 1;
dfs1(dfs1, root);
dfs2(dfs2, root, root);

/*

// 求 LCA //
auto LCA = [&](int a, int b) -> int {
    while (top[a] != top[b]) {
        if (depth[top[a]] < depth[top[b]]) std::swap(a, b);
        a = fa[top[a]];
    }
    return (depth[a] > depth[b] ? b : a);
};

// 维护 u 到 v 的路径 //
while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
    opt(dfn[top[u]], dfn[u]);
    u = fa[top[u]];
}
if (dfn[u] > dfn[v]) std::swap(u, v);
opt(dfn[u], dfn[v]);

// 维护 u 为根的子树 //
opt(dfn[u], botton[u]);

*/

// segment tree //

/* 
build() 函数中 
if(l == r) tree[u] = {l, l, w[rank[l]], 0}; 
*/
build(1, 1, n);

for (int i = 1; i <= m; i++) {
    int op, u, v;
    LL k;
    std::cin >> op;
    if (op == 1) {
        std::cin >> u >> v >> k;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
            modify(1, dfn[top[u]], dfn[u], k);
            u = fa[top[u]];
        }
        if (dfn[u] > dfn[v]) std::swap(u, v);
        modify(1, dfn[u], dfn[v], k);
    } else if (op == 2) {
        std::cin >> u >> v;
        LL ans = 0;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
            ans = (ans + query(1, dfn[top[u]], dfn[u])) % p;
            u = fa[top[u]];
        }
        if (dfn[u] > dfn[v]) std::swap(u, v);
        ans = (ans + query(1, dfn[u], dfn[v])) % p;
        std::cout << ans << endl;
    } else if (op == 3) {
        std::cin >> u >> k;
        modify(1, dfn[u], botton[u], k);
    } else {
        std::cin >> u;
        std::cout << query(1, dfn[u], botton[u]) % p << endl;
    }
}
```

