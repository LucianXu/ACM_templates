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
#define endl '\n'
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;
    vvi e(n + 1);
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    vpi ans1, ans2;
    vi vis(n + 1);
    auto dfs = [&](auto&& self, int u) -> void {
        vis[u] = 1;
        for (const auto& v : e[u]) {
            if (vis[v]) continue;
            ans1.emplace_back(u, v);
            self(self, v);
        }
    };
    dfs(dfs, 1);

    std::fill(all(vis), 0);
    auto bfs = [&](int u) -> void {
        std::queue<int> q;
        q.push(u);
        vis[u] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& v : e[u]) {
                if (vis[v]) continue;
                ans2.emplace_back(u, v);
                q.push(v);
                vis[v] = 1;
            }
        }
    };
    bfs(1);

    for (const auto& [u, v] : ans1) {
        std::cout << u << ' ' << v << endl;
    }
    for (const auto& [u, v] : ans2) {
        std::cout << u << ' ' << v << endl;
    }

    return 0;
}
