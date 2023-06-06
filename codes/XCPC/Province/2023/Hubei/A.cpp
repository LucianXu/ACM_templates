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

const int N = 2e5 + 10;

// struct edge {
//     int from, to;
//     LL cap, cost;

//     edge(int u, int v, LL c, LL w) : from(u), to(v), cap(c), cost(w) {}
// };

// struct node {
//     int v, e;

//     node(int _v = 0, int _e = 0) : v(_v), e(_e) {}
// };

// const int maxn = 5000 + 10;

// struct MCMF {
//     int n, m = 0, s, t;
//     std::vector<edge> e;
//     vi g[maxn];
//     int dis[maxn], vis[maxn], h[maxn];
//     node p[maxn * 2];

//     void init() {
//         m = 0;
//         e.clear();
//         for (int i = 1; i <= n; i++) {
//             g[i].clear();
//             p[i] = node(0, 0);
//         }
//     }

//     void add(int from, int to, LL cap, LL cost) {
//         e.push_back(edge(from, to, cap, cost));
//         e.push_back(edge(to, from, 0, -cost));
//         g[from].push_back(m++);
//         g[to].push_back(m++);
//     }

//     bool dijkstra() {
//         std::priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
//         for (int i = 1; i <= n; i++) {
//             dis[i] = inf;
//             vis[i] = 0;
//         }
//         dis[s] = 0;
//         q.push({0, s});
//         while (!q.empty()) {
//             int u = q.top().ss;
//             q.pop();
//             if (vis[u]) continue;
//             vis[u] = 1;
//             for (auto i : g[u]) {
//                 edge ee = e[i];
//                 int v = ee.to, nc = ee.cost + h[u] - h[v];
//                 if (ee.cap and dis[v] > dis[u] + nc) {
//                     dis[v] = dis[u] + nc;
//                     p[v] = node(u, i);
//                     if (!vis[v]) q.push({dis[v], v});
//                 }
//             }
//         }
//         return dis[t] != inf;
//     }

//     void spfa() {
//         std::queue<int> q;
//         for (int i = 1; i <= n; i++) h[i] = inf;
//         h[s] = 0, vis[s] = 1;
//         q.push(s);
//         while (!q.empty()) {
//             int u = q.front();
//             q.pop();
//             vis[u] = 0;
//             for (auto i : g[u]) {
//                 edge ee = e[i];
//                 int v = ee.to;
//                 if (ee.cap and h[v] > h[u] + ee.cost) {
//                     h[v] = h[u] + ee.cost;
//                     if (!vis[v]) {
//                         vis[v] = 1;
//                         q.push(v);
//                     }
//                 }
//             }
//         }
//     }

//     PLL mcmf() {
//         LL maxf = 0, minc = 0;
//         spfa();
//         while (dijkstra()) {
//             LL minf = INF;
//             for (int i = 1; i <= n; i++) h[i] += dis[i];
//             for (int i = t; i != s; i = p[i].v) minf = std::min(minf, e[p[i].e].cap);
//             for (int i = t; i != s; i = p[i].v) {
//                 e[p[i].e].cap -= minf;
//                 e[p[i].e ^ 1].cap += minf;
//             }
//             maxf += minf;
//             minc += minf * h[t];
//         }
//         return std::make_pair(maxf, minc);
//     }
// } minc_maxf;

struct edge {
    int from, to;
    LL cap, flow;

    edge(int u, int v, LL c, LL f) : from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
    int n, m = 0, s, t;
    std::vector<edge> e;
    vi g[N];
    int d[N], cur[N], vis[N];

    void init() {
        for (int i = 0; i <= n; i++) g[i].clear();
        e.clear();
        m = 0;
    }

    void add(int from, int to, LL cap) {
        e.push_back(edge(from, to, cap, 0));
        e.push_back(edge(to, from, 0, 0));
        g[from].push_back(m++);
        g[to].push_back(m++);
    }

    bool bfs() {
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
        }
        std::queue<int> q;
        q.push(s), d[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); i++) {
                edge& ee = e[g[u][i]];
                if (!vis[ee.to] and ee.cap > ee.flow) {
                    vis[ee.to] = 1;
                    d[ee.to] = d[u] + 1;
                    q.push(ee.to);
                }
            }
        }
        return vis[t];
    }

    LL dfs(int u, LL now) {
        if (u == t || now == 0) return now;
        LL flow = 0, f;
        for (int& i = cur[u]; i < g[u].size(); i++) {
            edge& ee = e[g[u][i]];
            edge& er = e[g[u][i] ^ 1];
            if (d[u] + 1 == d[ee.to] and (f = dfs(ee.to, std::min(now, ee.cap - ee.flow))) > 0) {
                ee.flow += f, er.flow -= f;
                flow += f, now -= f;
                if (now == 0) break;
            }
        }
        return flow;
    }

    LL dinic() {
        LL ans = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++) cur[i] = 0;
            ans += dfs(s, INF);
        }
        return ans;
    }
} maxf;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    vi prime, is_prime(1000010);
    for (int i = 2; i <= 1000000; i++) {
        if (!is_prime[i]) prime.push_back(i);
        for (auto p : prime) {
            if (i * p >= 1000000) break;
            is_prime[i * p] = 1;
            if (i % p == 0) break;
        }
    }

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        vi a(n + 2);
        for (int i = 1; i <= n; i++) std::cin >> a[i];
        for (int i = n; i >= 1; i--) a[i] -= a[i - 1];

        maxf.n = n + 3, maxf.s = n + 2, maxf.t = n + 3;
        for (int i = 1; i <= n; i++) {
            if (a[i] > 0) {
                maxf.add(maxf.s, i, a[i]);
            } else if (a[i] < 0) {
                maxf.add(i, maxf.t, -a[i]);
            }
        }

        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= 0) continue;
            if (~abs(n + 1 - i) & 1) {
                res += 2 * (-a[i]);
            } else if (is_prime[n + 1 - i]) {
                res += 3 * (-a[i]);
            } else {
                res += (-a[i]);
            }
        }
        debug(res);

        // 费用为 3 的优化为费用为 1 的 //
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i] <= 0 or a[j] >= 0) continue;
                if (abs(i - j) & 1 and !is_prime[abs(i - j)] and (n + 1 - j) & 1 and
                    is_prime[n + 1 - j]) {
                    maxf.add(i, j, inf);
                }
            }
        }

        res -= 2 * maxf.dinic();

        // 费用为 3 的优化为费用为 2 的 以及 费用为 2 的优化为费用为 1 的 //
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i] <= 0 or a[j] >= 0) continue;
                if (~abs(i - j) & 1 and (n + 1 - j) & 1 and is_prime[n + 1 - j]) {
                    maxf.add(i, j, inf);
                } else if (abs(i - j) & 1 and !is_prime[abs(i - j)] and ~(n + 1 - j) & 1) {
                    maxf.add(i, j, inf);
                }
            }
        }

        res -= maxf.dinic();

        std::cout << res << '\n';

        maxf.init();
    }
    return 0;
}
