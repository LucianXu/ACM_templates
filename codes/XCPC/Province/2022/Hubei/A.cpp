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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        int n, m, k;
        int ti;
        std::cin >> n >> m >> k;
        std::cin >> ti;
        vvl g(n + 1, vl(n + 1, INF));
        for (int i = 1; i <= n; i++) g[i][i] = 0;
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            std::cin >> a >> b >> c;
            g[a][b] = g[b][a] = std::min(g[a][b], (LL) c);
        }

        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }

        std::vector<bool> he(n + 1);
        for (int i = 1; i <= k; i++) {
            int x;
            std::cin >> x;
            he[x] = true;
        }

        if (ti == 0) {
            std::cout << -1 << '\n';
            return 0;
        }
        LL res = 0;
        for (int i = 1; i <= n; i++) {
            if (!he[i]) {
                LL w = INF;
                for (int j = 1; j <= n; j++)
                    if (he[j]) w = std::min(w, (2 * g[i][j]));
                Max(res, w);
            }
        }

        for (int i = 1; i <= n; i++)
            if (g[i][1] == INF) {
                std::cout << -1 << '\n';
                return 0;
            }

        vpi temp;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (he[i] && he[j]) temp.push_back({i, j});
            }
        }

        std::sort(all(temp), [&](PII& a, PII& b) { return g[a.ff][a.ss] < g[b.ff][b.ss]; });

        vi dsu(n + 1);
        std::iota(all(dsu), 0);

        std::function<int(int)> find = [&](int x) -> int {
            if (x != dsu[x]) dsu[x] = find(dsu[x]);
            return dsu[x];
        };

        for (auto& [i, j] : temp) {
            int fi = find(i), fj = find(j);
            if (fi != fj) {
                dsu[fi] = fj;
                Max(res, g[i][j]);
            }
        }

        std::cout << (res + ti - 1) / ti << '\n';
    }
    return 0;
}
