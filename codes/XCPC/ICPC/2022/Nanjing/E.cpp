// created on Lucian Xu's Laptop

#include <bits/stdc++.h>

// using namespace std;

typedef unsigned int UI;
typedef unsigned long long ULL;
typedef long long LL;
typedef unsigned long long ULL;
typedef __int128 i128;
typedef std::pair<int, int> PII;
typedef std::pair<int, LL> PIL;
typedef std::pair<LL, int> PLI;
typedef std::pair<LL, LL> PLL;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<LL> vl;
typedef std::vector<vl> vvl;
typedef std::vector<PII> vpi;

#define typet typename T
#define typeu typename U
#define types typename... Ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) \
    do {           \
    } while (false)
#endif

constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
constexpr int inf = 0x3f3f3f3f;
constexpr LL INF = 1e18;
constexpr double pi = 3.141592653589793;
constexpr double eps = 1e-6;

constexpr int lowbit(int x) { return x & -x; }
constexpr int add(int x, int y) { return x + y < mod ? x + y : x - mod + y; }
constexpr int sub(int x, int y) { return x < y ? mod + x - y : x - y; }
constexpr int mul(LL x, int y) { return x * y % mod; }
constexpr void Add(int& x, int y) { x = add(x, y); }
constexpr void Sub(int& x, int y) { x = sub(x, y); }
constexpr void Mul(int& x, int y) { x = mul(x, y); }
constexpr int pow(int x, int y, int z = 1) {
    for (; y; y /= 2) {
        if (y & 1) Mul(z, x);
        Mul(x, x);
    }
    return z;
}
temps constexpr int add(Ts... x) {
    int y = 0;
    (..., Add(y, x));
    return y;
}
temps constexpr int mul(Ts... x) {
    int y = 1;
    (..., Mul(y, x));
    return y;
}

tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

void solut() {
    int n;
    std::cin >> n;
    vi a(n);
    vvi e(n + 1);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    // ST 表 //
    // 查询 a 的区间 min //
    vvi val(n, vi(30, inf));
    vi Log2(n + 1);
    auto ST_init = [&]() -> void {
        for (int i = 0; i < n; i++) {
            val[i][0] = a[i];
            if (i > 1) Log2[i] = Log2[i / 2] + 1;
        };
        Log2[n] = Log2[n / 2] + 1;
        int t = Log2[n];
        for (int j = 1; j <= t; j++) {
            for (int i = 0; i <= n - (1 << j); i++) {
                val[i][j] = std::min(val[i][j - 1], val[i + (1 << (j - 1))][j - 1]);
            }
        }
    };
    ST_init();

    auto ST_query = [&](int l, int r) -> int {
        int t = Log2[r - l + 1];
        return std::min(val[l][t], val[r - (1 << t) + 1][t]);
    };

    // LCA //
    // 同时处理 dfn 序 //
    int timestamp = 0, root = 1;
    vi dep(n + 1), dfn(n + 1);
    vvi fa(n + 1, vi(50));

    auto dfs = [&](auto&& self, int u) -> void {
        dfn[u] = ++timestamp;
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

    vvi layer(n + 1), g(n + 1);
    vl f(n + 1, INF);    // dp 值 //
    for (int i = 1; i <= n; i++) layer[dep[i]].push_back(i);

    // vertual tree //
    auto build_vtree = [&](vvi& g, vi& ver) -> void {
        std::sort(all(ver), [&](int x, int y) { return dfn[x] < dfn[y]; });
        vi stk = {1};
        for (auto v : ver) {
            int u = stk.back();
            int lca = LCA(v, u);
            if (lca != u) {
                while (dfn[lca] < dfn[stk.end()[-2]]) {
                    g[stk.end()[-2]].push_back(stk.back());
                    stk.pop_back();
                }
                u = stk.back();
                if (dfn[lca] != dfn[stk.end()[-2]]) {
                    g[lca].push_back(u);
                    stk.pop_back();
                    stk.push_back(lca);
                } else {
                    g[lca].push_back(u);
                    stk.pop_back();
                }
            }
            stk.push_back(v);
        }
        while (stk.size() > 1) {
            int u = stk.end()[-2];
            int v = stk.back();
            g[u].push_back(v);
            stk.pop_back();
        }
    };

    // 虚树上树形 dp //
    auto dp = [&](auto&& self, int u, int d, int dNow) -> void {
        if (g[u].empty()) return;
        LL res = 0;
        for (const auto& v : g[u]) {
            f[v] = ST_query(d - dep[v], d - dep[u] - 1);
            self(self, v, d, dNow + 1);
            res += f[v];
        }
        Min(f[u], res);
    };

    // 虚树复原 //
    auto clear = [&](auto&& self, int u) -> void {
        for (const auto v : g[u]) {
            self(self, v);
        }
        f[u] = INF;
        g[u].clear();
    };

    LL ans = 0;
    for (int i = 2; i <= n; i++) {    // 分层在建立虚树在虚树上 dp //
        if (layer[i].empty()) continue;
        build_vtree(g, layer[i]);
        f[1] = a[i - 1];
        dp(dp, 1, i, 1);
        ans += f[1];
        clear(clear, 1);
    }

    std::cout << ans + a[0] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
