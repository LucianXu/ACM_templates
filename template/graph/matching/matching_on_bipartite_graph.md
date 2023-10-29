# 二分图最大匹配

## Kuhn-Munkres 算法

时间复杂度：$O(n^3)$。

```cpp
auto KM = [&](int n1, int n2, vvi e) -> std::pair<vi, vi> {
    vi vis(n2 + 1);
    vi l(n1 + 1, -1), r(n2 + 1, -1);
    std::function<bool(int)> dfs = [&](int u) -> bool {
        for (auto v : e[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                if (r[v] == -1 or dfs(r[v])) {
                    r[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    for (int i = 1; i <= n1; i++) {
        std::fill(all(vis), 0);
        dfs(i);
    }
    for (int i = 1; i <= n2; i++) {
        if (r[i] == -1) continue;
        l[r[i]] = i;
    }
    return {l, r};
};
auto [mchl, mchr] = KM(n1, n2, e);
std::cout << mchl.size() - std::count(all(mchl), -1) << endl;
```

## Hopcroft-Karp 算法

据说时间复杂度是 $O(m \sqrt{n})$ 的，但是快的飞起。

```cpp
vpi e(m);
auto hopcroft_karp = [&](int n, int m, vpi& e) -> std::pair<vi, vi> {
    vi g(e.size()), l(n + 1, -1), r(m + 1, -1), d(n + 2);
    for (auto [u, v] : e) d[u]++;
    std::partial_sum(all(d), d.begin());
    for (auto [u, v] : e) g[--d[u]] = v;
    for (vi a, p, q(n + 1);;) {
        a.assign(n + 1, -1);
        p.assign(n + 1, -1);
        int t = 1;
        for (int i = 1; i <= n; i++) {
            if (l[i] == -1) {
                q[t++] = a[i] = p[i] = i;
            }
        }
        bool match = false;
        for (int i = 1; i < t; i++) {
            int u = q[i];
            if (l[a[u]] != -1) continue;
            for (int j = d[u]; j < d[u + 1]; j++) {
                int v = g[j];
                if (r[v] == -1) {
                    while (v != -1) {
                        r[v] = u;
                        std::swap(l[u], v);
                        u = p[u];
                    }
                    match = true;
                    break;
                }
                if (p[r[v]] == -1) {
                    q[t++] = v = r[v];
                    p[v] = u;
                    a[v] = a[u];
                }
            }
        }
        if (!match) break;
    }
    return {l, r};
};
```

# 二分图最大权匹配

## Kuhn_Munkres 算法

注意是否为完美匹配，非完美选 $0$，完美选 $-INF$。

```cpp
auto KM = [&](int n, vvl e) -> std::tuple<LL, vi, vi> {
    vl la(n + 1), lb(n + 1), pp(n + 1), vx(n + 1);
    vi l(n + 1, -1), r(n + 1, -1);
    vi va(n + 1), vb(n + 1);
    LL delta;
    auto bfs = [&](int x) -> void {
        int a, y = 0, y1 = 0;
        std::fill(all(pp), 0);
        std::fill(all(vx), INF);
        r[y] = x;
        do {
            a = r[y], delta = INF, vb[y] = 1;
            for (int b = 1; b <= n; b++) {
                if (!vb[b]) {
                    if (vx[b] > la[a] + lb[b] - e[a][b]) {
                        vx[b] = la[a] + lb[b] - e[a][b];
                        pp[b] = y;
                    }
                    if (vx[b] < delta) {
                        delta = vx[b];
                        y1 = b;
                    }
                }
            }
            for (int b = 0; b <= n; b++) {
                if (vb[b]) {
                    la[r[b]] -= delta;
                    lb[b] += delta;
                } else
                    vx[b] -= delta;
            }
            y = y1;
        } while (r[y] != -1);
        while (y) {
            r[y] = r[pp[y]];
            y = pp[y];
        }
    };
    for (int i = 1; i <= n; i++) {
        std::fill(all(vb), 0);
        bfs(i);
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        if (r[i] == -1) continue;
        l[r[i]] = i;
        ans += e[r[i]][i];
    }
    return {ans, l, r};
};

auto [ans, mchl, mchr] = KM(n, e);
```

