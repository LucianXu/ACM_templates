# 树分治

## 点分治

### 第一个题

一棵 $n \leqslant 10^4$ 个点的树，边权 $w \leqslant 10^4$。 $m \leqslant 100$ 次询问树上是否存在长度为 $k \leqslant 10^7$ 的路径。

```cpp
// 洛谷 P3806 【模板】点分治1

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, k;
    std::cin >> n >> m;

    std::vector<vpi> e(n + 1);
    std::map<int, PII> mp;

    for (int i = 1; i < n; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> k;
        mp[i] = {k, 0};
    }

    // centroid decomposition //
    int top1 = 0, top2 = 0, root;
    vi len1(n + 1), len2(n + 1), vis(n + 1);
    static std::array<int, 20000010> cnt;

    std::function<int(int, int)> get_size = [&](int u, int fa) -> int {
        if (vis[u]) return 0;
        int ans = 1;
        for (auto [v, w] : e[u]) {
            if (v == fa) continue;
            ans += get_size(v, u);
        }
        return ans;
    };

    std::function<int(int, int, int, int&)> get_root = [&](int u, int fa, int tot,
                                                           int& root) -> int {
        if (vis[u]) return 0;
        int sum = 1, maxx = 0;
        for (auto [v, w] : e[u]) {
            if (v == fa) continue;
            int tmp = get_root(v, u, tot, root);
            Max(maxx, tmp);
            sum += tmp;
        }
        Max(maxx, tot - sum);
        if (2 * maxx <= tot) root = u;
        return sum;
    };

    std::function<void(int, int, int)> get_dist = [&](int u, int fa, int dist) -> void {
        if (dist <= 10000000) len1[++top1] = dist;
        for (auto [v, w] : e[u]) {
            if (v == fa or vis[v]) continue;
            get_dist(v, u, dist + w);
        }
    };

    auto solve = [&](int u, int dist) -> void {
        top2 = 0;
        for (auto [v, w] : e[u]) {
            if (vis[v]) continue;
            top1 = 0;
            get_dist(v, u, w);
            for (int i = 1; i <= top1; i++) {
                for (int tt = 1; tt <= m; tt++) {
                    int k = mp[tt].ff;
                    if (k >= len1[i]) mp[tt].ss |= cnt[k - len1[i]];
                }
            }
            for (int i = 1; i <= top1; i++) {
                len2[++top2] = len1[i];
                cnt[len1[i]] = 1;
            }
        }
        for (int i = 1; i <= top2; i++) cnt[len2[i]] = 0;
    };

    std::function<void(int)> divide = [&](int u) -> void {
        vis[u] = cnt[0] = 1;
        solve(u, 0);
        for (auto [v, w] : e[u]) {
            if (vis[v]) continue;
            get_root(v, u, get_size(v, u), root);
            divide(root);
        }
    };

    get_root(1, 0, get_size(1, 0), root);
    divide(root);

    for (int i = 1; i <= m; i++) {
        if (mp[i].ss == 0) {
            std::cout << "NAY" << endl;
        } else {
            std::cout << "AYE" << endl;
        }
    }

    return 0;
}
```

### 第二个题

一棵 $n \leqslant 4 \times 10^4$ 个点的树，边权 $w \leqslant 10^3$。询问树上长度不超过 $k \leqslant 2 \times 10^4$ 的路径的数量。

```cpp
// 洛谷 P4178 Tree

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, k;
    std::cin >> n;
    std::vector<vpi> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    std::cin >> k;

    // centroid decomposition //
    int root;
    vi len, vis(n + 1);

    std::function<int(int, int)> get_size = [&](int u, int fa) -> int {
        if (vis[u]) return 0;
        int ans = 1;
        for (auto [v, w] : e[u]) {
            if (v == fa) continue;
            ans += get_size(v, u);
        }
        return ans;
    };

    std::function<int(int, int, int, int&)> get_root = [&](int u, int fa, int tot,
                                                           int& root) -> int {
        if (vis[u]) return 0;
        int sum = 1, maxx = 0;
        for (auto [v, w] : e[u]) {
            if (v == fa) continue;
            int tmp = get_root(v, u, tot, root);
            maxx = std::max(maxx, tmp);
            sum += tmp;
        }
        maxx = std::max(maxx, tot - sum);
        if (2 * maxx <= tot) root = u;
        return sum;
    };

    std::function<void(int, int, int)> get_dist = [&](int u, int fa, int dist) -> void {
        len.push_back(dist);
        for (auto [v, w] : e[u]) {
            if (v == fa || vis[v]) continue;
            get_dist(v, u, dist + w);
        }
    };

    auto solve = [&](int u, int dist) -> int {
        len.clear();
        get_dist(u, 0, dist);
        std::sort(all(len));
        int ans = 0;
        for (int l = 0, r = len.size() - 1; l < r;) {
            if (len[l] + len[r] <= k) {
                ans += r - l++;
            } else {
                r--;
            }
        }
        return ans;
    };

    std::function<int(int)> divide = [&](int u) -> int {
        vis[u] = true;
        int ans = solve(u, 0);
        for (auto [v, w] : e[u]) {
            if (vis[v]) continue;
            ans -= solve(v, w);
            get_root(v, u, get_size(v, u), root);
            ans += divide(root);
        }
        return ans;
    };

    get_root(1, 0, get_size(1, 0), root);
    std::cout << divide(root) << endl;

    return 0;
}
```

