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

struct node {
    LL g1 = 0, g2 = 0;
    node(LL _g1 = 0, LL _g2 = 0) { g1 = _g1, g2 = _g2; }
    LL gcd() {
        if (g1 == -1) return 0;
        return std::gcd(g1, g2);
    }
};

node merge(node x, node y) {
    if (x.g1 == -1) {
        return y;
    } else if (y.g1 == -1) {
        return x;
    } else {
        return node(x.g1, std::gcd(std::gcd(x.g2, y.g2), abs(x.g1 - y.g1)));
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, k;
    std::cin >> n >> k;
    vi c(n + 1);
    for (int i = 1, x; i <= k; i++) {
        std::cin >> x;
        c[x] = 1;
    }
    std::vector<vpi> e(n + 1);
    std::vector<node> gcd(n + 1), gcd_fa(n + 1), gcd_final(n + 1);
    for (int i = 1, u, v, w; i <= n - 1; i++) {
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    if (k == 1) {
        std::cout << 0 << '\n';
        return 0;
    }

    vi siz(n + 1);
    vl dist(n + 1);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        siz[u] = c[u];
        gcd[u] = c[u] ? node(0, 0) : node(-1, -1);
        for (const auto& [v, w] : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            siz[u] += siz[v];
            dist[u] += dist[v] + 1ll * w * siz[v];
            node g = gcd[v];
            if (g.g1 != -1) g.g1 += w;
            gcd[u] = merge(gcd[u], g);
        }
    };
    dfs(dfs, 1, 0);

    auto dfss = [&](auto&& self, int u, int fa) -> void {
        gcd_final[u] = merge(gcd[u], gcd_fa[u]);
        std::vector<node> gg;
        for (const auto& [v, w] : e[u]) {
            if (v == fa) {
                gg.push_back(node(-1, -1));
                continue;
            }
            node g = gcd[v];
            if (g.g1 != -1) g.g1 += w;
            gg.push_back(g);
        }
        int m = e[u].size();
        std::vector<node> pre(m), suf(m);
        pre[0] = gg[0];
        suf[m - 1] = gg[m - 1];
        for (int i = 1; i < m; i++) {
            pre[i] = merge(gg[i], pre[i - 1]);
        }
        for (int i = m - 2; i >= 0; i--) {
            suf[i] = merge(gg[i], suf[i + 1]);
        }
        for (int i = 0; i < m; i++) {
            const auto& [v, w] = e[u][i];
            if (v == fa) continue;
            gcd_fa[v] = gcd_fa[u];
            if (i != 0) {
                gcd_fa[v] = merge(gcd_fa[v], pre[i - 1]);
            }
            if (i != m - 1) {
                gcd_fa[v] = merge(gcd_fa[v], suf[i + 1]);
            }
            if (gcd_fa[v].g1 != -1) gcd_fa[v].g1 += w;
            if (c[v]) {
                gcd_fa[v] = merge(gcd_fa[v], node(0, 0));
            }
            dist[v] = dist[u] + 1ll * w * (k - 2 * siz[v]);
            self(self, v, u);
        }
    };
    gcd_fa[1] = c[1] ? node(0, 0) : node(-1, -1);
    dfss(dfss, 1, 0);

    LL ans = INF;
    for (int i = 1; i <= n; i++) {
        if (gcd_final[i].gcd() > 0) {
            Min(ans, dist[i] / gcd_final[i].gcd());
        }
    }
    std::cout << ans * 2 << '\n';

    return 0;
}
