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

    int n, m, k;
    std::cin >> n >> m >> k;
    vvi e(n + 1), dist(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    auto bfs = [&](int s) -> vi {
        vi dis(n + 1, inf);
        dis[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : e[u]) {
                if (dis[v] != inf) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return dis;
    };

    auto get = [&](int x, int t) -> double {
        if (x == 0) return 0;
        return (double) (t % x) * (1.0 / (t / x + 2)) + (double) (x - t % x) * (1.0 / (t / x + 1));
    };

    auto check = [&](int x, int y) -> bool { return dist[x][y] != inf; };

    for (int i = 1; i <= n; i++) {
        dist[i] = bfs(i);
    }

    int sa, ta, sb, tb;
    double ans = inf;
    std::cin >> sa >> ta >> sb >> tb;
    vi mapple(m + 1, inf);
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (!check(u, v)) continue;
            int x = dist[u][v], y;
            // sa - u - v - ta  sb - u - v - tb //
            if (check(sa, u) and check(v, ta) and check(sb, u) and check(v, tb)) {
                int y = dist[sa][u] + dist[v][ta] + dist[sb][u] + dist[v][tb];
                mapple[x] = std::min(mapple[x], y);
            }
            // sa - u - v - ta  sb - v - u - tb //
            if (check(sa, u) and check(v, ta) and check(sb, v) and check(u, tb)) {
                y = dist[sa][u] + dist[v][ta] + dist[sb][v] + dist[u][tb];
                mapple[x] = std::min(mapple[x], y);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (mapple[i] == inf) continue;
        int x = i, y = mapple[i];
        int l = 0, r = k;
        while (l + 100 < r) {
            int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
            double lsum = 2 * get(x, lmid) + get(y, k - lmid);
            double rsum = 2 * get(x, rmid) + get(y, k - rmid);
            if (lsum < rsum)
                r = rmid - 1;
            else
                l = lmid + 1;
        }
        for (int t = l; t <= r; t++) {
            ans = std::min(ans, 2 * get(x, t) + get(y, k - t));
        }
    }
    Min(ans, get(dist[sa][ta] + dist[sb][tb], k));
    std::cout << std::fixed << std::setprecision(10) << ans << '\n';

    return 0;
}
