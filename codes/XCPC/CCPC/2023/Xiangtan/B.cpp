// created on Lucian Xu's Laptop

#include <bits/stdc++.h>

// using namespace std;

#define typet typename T
#define typeu typename U
#define types typename... Ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

using UI = unsigned int;
using ULL = unsigned long long;
using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using PII = std::pair<int, int>;
using PIL = std::pair<int, LL>;
using PLI = std::pair<LL, int>;
using PLL = std::pair<LL, LL>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vl = std::vector<LL>;
using vvl = std::vector<vl>;
using vpi = std::vector<PII>;

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
tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

void solut() {
    int n, m;
    std::cin >> n >> m;
    std::vector e(2 * n + 1, std::vector<PIL>());
    for (int i = 1, u, v, w; i <= m; i++) {
        std::cin >> u >> v >> w;
        u++, v++;
        if (w & 1) {
            e[u + n].emplace_back(v, w);
            e[u].emplace_back(v + n, w);
        } else {
            e[u].emplace_back(v, w);
            e[u + n].emplace_back(v + n, w);
        }
    }

    // SCC //
    vi dfn(2 * n + 1), low(2 * n + 1), stk(2 * n + 1), belong(2 * n + 1);
    int timestamp = 0, top = 0, scc_cnt = 0;
    vvi scc(2 * n + 1);
    std::vector<bool> in_stk(2 * n + 1);

    auto tarjan = [&](auto&& self, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
        in_stk[u] = true;
        for (const auto& [v, w] : e[u]) {
            if (!dfn[v]) {
                self(self, v);
                Min(low[u], low[v]);
            } else if (in_stk[v]) {
                Min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            int v;
            do {
                v = stk[top--];
                in_stk[v] = false;
                belong[v] = scc_cnt;
            } while (v != u);
        }
    };
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) tarjan(tarjan, i);
    }
    for (int i = 1; i <= 2 * n; i++) scc[belong[i]].push_back(i);

    // 负环 //
    vl dist1(2 * n + 1);
    vi vis(2 * n + 1), cnt(2 * n + 1);

    auto spfa = [&](int id) -> bool {
        std::queue<int> q;
        for (const auto& u : scc[id]) {
            q.push(u);
            vis[u] = false;
        }
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            vis[u] = false;
            for (auto [v, w] : e[u]) {
                if (belong[v] != id) continue;
                if (dist1[v] > dist1[u] + w) {
                    dist1[v] = dist1[u] + w;
                    Max(cnt[v], cnt[u] + 1);
                    if (cnt[v] >= scc[id].size()) return true;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return false;
    };

    // Johnson 最短路 //
    vl dist2(2 * n + 1);

    auto dijkstra = [&](int s, int id) {
        for (const auto& u : scc[id]) {
            dist2[u] = INF;
            vis[u] = false;
        }
        dist2[s] = 0;
        std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> q;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (const auto& [v, w] : e[u]) {
                if (dist2[v] > d + w) {
                    dist2[v] = d + w;
                    q.emplace(dist2[v], v);
                }
            }
        }
    };

    vl ans(2 * n + 1, INF);
    for (int id = 1; id <= scc_cnt; id++) {
        // solve //
        if (spfa(id)) {    // 存在负环 //
            for (const auto& u : scc[id]) {
                if (u > n) continue;
                if (belong[u] != belong[u + n]) {    // 不连通 //
                    continue;
                } else {    // 可走负环 //
                    ans[u] = -INF;
                }
            }
        } else {    // 不存在负环 //
            for (const auto& u : scc[id]) {
                for (auto& [v, w] : e[u]) {
                    w += dist1[u] - dist1[v];
                }
            }
            for (const auto& u : scc[id]) {
                if (u > n) continue;
                if (belong[u] != belong[u + n]) {    // 不连通 //
                    continue;
                } else {    // Johnson //
                    dijkstra(u + n, id);
                    ans[u] = dist2[u] + dist1[u] - dist1[u + n];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == -INF) {
            std::cout << "Haha, stupid Honkai" << '\n';
        } else if (ans[i] == INF) {
            std::cout << "Battle with the crazy Honkai" << '\n';
        } else {
            std::cout << ans[i] << '\n';
        }
    }
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
