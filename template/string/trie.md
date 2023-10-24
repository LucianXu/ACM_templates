# 字典树

## 普通字典树（单词匹配）

```cpp

// trie //
int cnt;
std::vector<std::array<int, 26>> trie(n + 1);
vi exist(n + 1);

auto insert = [&](const std::string& s) -> void {
    int p = 0;
    for (const auto ch : s) {
        int c = ch - 'a';
        if (!trie[p][c]) trie[p][c] = ++cnt;
        p = trie[p][c];
    }
    exist[p] = true;
};

auto find = [&](const string& s) -> bool {
    int p = 0;
    for (const auto ch : s) {
        int c = ch - 'a';
        if (!trie[p][c]) return false;
        p = trie[p][c];
    }
    return exist[p];
};
```

## 01字典树（求最大异或值）

给定 $n$ 个数，取两个数进行异或运算，求最大异或值。

```cpp
// trie //
int cnt = 0;
std::vector<std::array<int, 2>> trie(N);

auto insert = [&](int x) -> void {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (!trie[p][c]) trie[p][c] = ++cnt;
        p = trie[p][c];
    }
};

auto find = [&](int x) -> int {
    int sum = 0, p = 0;
    for (int i = 30; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (trie[p][c ^ 1]) {
            p = trie[p][c ^ 1];
            sum += (1 << i);
        } else {
            p = trie[p][c];
        }
    }
    return sum;
};
```

## 字典树合并

来自浙大城市学院 2023 校赛 E 题。

给定一棵根为 $1$ 的树，每个点的点权为 $w_i$。一共 $q$ 次询问，每次给出一对 $u$，$v$，询问以 $v$ 为根的子树上的点与 $u$ 的权值最大异或值。

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n;
    vi w(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }

    vvi e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    // 离线询问 //
    std::cin >> m;
    std::vector<vpi> q(n + 1);
    vi ans(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        q[v].emplace_back(u, i);
    }

    // 01 trie //
    std::vector<std::array<int, 2>> tr(1);

    auto new_node = [&]() -> int {
        tr.emplace_back();
        return tr.size() - 1;
    };

    vi id(n + 1);

    auto insert = [&](int root, int x) {
        int p = root;
        for (int i = 29; i >= 0; i--) {
            int c = x >> i & 1;
            if (!tr[p][c]) tr[p][c] = new_node();
            p = tr[p][c];
        }
    };

    auto query = [&](int root, int x) -> int {
        int ans = 0, p = root;
        for (int i = 29; i >= 0; i--) {
            int c = x >> i & 1;
            if (tr[p][c ^ 1]) {
                p = tr[p][c ^ 1];
                ans += (1 << i);
            } else {
                p = tr[p][c];
            }
        }
        return ans;
    };

    std::function<int(int, int)> merge = [&](int a, int b) -> int {
        // b 的信息挪到 a 上 //
        if (!a) return b;
        if (!b) return a;
        tr[a][0] = merge(tr[a][0], tr[b][0]);
        tr[a][1] = merge(tr[a][1], tr[b][1]);
        return a;
    };

    std::function<void(int, int)> dfs = [&](int u, int fa) {
        id[u] = new_node();
        insert(id[u], w[u]);
        for (auto v : e[u]) {
            if (v == fa) continue;
            dfs(v, u);
            id[u] = merge(id[u], id[v]);
        }
        for (auto [v, i] : q[u]) {
            ans[i] = query(id[u], w[v]);
        }
    };
    dfs(1, 0);

    for (int i = 1; i <= m; i++) std::cout << ans[i] << endl;

    return 0;
}
```

