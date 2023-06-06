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
    vi a(n + 1), val_1, val_2;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        val_1.push_back(a[i] + i);
        val_2.push_back(a[i] - i);
    }
    std::sort(all(val_1));
    std::sort(all(val_2));
    val_1.erase(unique(all(val_1)), val_1.end());
    val_2.erase(unique(all(val_2)), val_2.end());

    vvi e(3 * n + 1);
    for (int i = 1; i <= n; i++) {
        int p1 = (std::lower_bound(all(val_1), a[i] + i) - val_1.begin()) + 1 + n;
        int p2 = (std::lower_bound(all(val_2), a[i] - i) - val_2.begin()) + 1 + n + val_1.size();
        e[i].push_back(p1);
        e[i].push_back(p2);
        e[p1].push_back(i);
        e[p2].push_back(i);
    }

    vi vis(3 * n + 1), dep(3 * n + 1);
    vi used(n + 1);
    vpi ans;

    auto bfs = [&](int s) -> int {
        int res = 0;
        std::queue<int> q;
        q.push(s);
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (1 <= u and u <= n) res += 1;
            for (const auto& v : e[u]) {
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        return res;
    };

    auto dfs = [&](auto&& self, int u, int fa, int d) -> void {
        debug(u);
        vis[u] = 1;
        dep[u] = d;
        for (const auto& v : e[u]) {
            if (dep[v]) continue;
            self(self, v, u, d + 1);
        }
        if (u > n) {
            vi ver;
            for (const auto& v : e[u]) {
                if (1 <= v and v <= n and !used[v] and dep[v] > dep[u]) ver.push_back(v);
            }
            debug(u, fa, ver);
            while (ver.size() > 1) {
                int x = ver.back();
                ver.pop_back();
                int y = ver.back();
                ver.pop_back();
                used[x] = used[y] = 1;
                ans.emplace_back(x, y);
            }
            if (ver.size() == 1) {
                int x = ver.back();
                used[x] = used[fa] = 1;
                ans.emplace_back(x, fa);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        debug("dfs", i);

        if (bfs(i) & 1) {
            std::cout << "No" << '\n';
            return;
        } else {
            dfs(dfs, i, 0, 1);
        }
    }

    std::cout << "Yes" << '\n';
    for (const auto& [u, v] : ans) std::cout << u << ' ' << v << '\n';
}


/*

// Another way //

void solut() {
    int n;
    std::cin >> n;
    vi a(n + 1), val_1, val_2;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        val_1.push_back(a[i] + i);
        val_2.push_back(a[i] - i);
    }
    std::sort(all(val_1));
    std::sort(all(val_2));
    val_1.erase(unique(all(val_1)), val_1.end());
    val_2.erase(unique(all(val_2)), val_2.end());

    std::vector<vpi> e(2 * n + 1);
    vi x(n + 1), y(n + 1);
    vi deg(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = (std::lower_bound(all(val_1), a[i] + i) - val_1.begin()) + 1;
        y[i] = (std::lower_bound(all(val_2), a[i] - i) - val_2.begin()) + 1 + val_1.size();
        e[x[i]].emplace_back(y[i], i);
        e[y[i]].emplace_back(x[i], i);
        deg[x[i]] += 1, deg[y[i]] += 1;
    }

    int cnt = 0;
    vi vis(2 * n + 1), dep(2 * n + 1);
    vi used(n + 1);
    vvi have(2 * n + 1);
    vpi ans;

    auto bfs = [&](int s) -> int {
        int res = 0;
        std::queue<int> q;
        q.push(s);
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            res += deg[u];
            for (const auto& [v, id] : e[u]) {
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        return res / 2;
    };

    auto dfs = [&](auto& self, int u, int fa) -> void {
        vis[u] = 1;
        for (const auto& [v, id] : e[u]) {
            if (v == fa) continue;
            if (vis[v]) {
                if (!used[id]) have[u].push_back(id);
            } else {
                self(self, v, u);
                have[have[v].size() & 1 ? v : u].push_back(id);
            }
            used[id] = 1;
        }
    };

    for (int i = 1; i <= val_1.size() + val_2.size(); i++) {
        if (vis[i]) continue;
        dfs(dfs, i, 0);
    }

    for (int i = 1; i <= val_1.size() + val_2.size(); i++) {
        if (have[i].size() & 1) {
            std::cout << "No" << '\n';
            return;
        }
    }

    std::cout << "Yes" << '\n';
    for (int i = 1; i <= val_1.size() + val_2.size(); i++) {
        for (int j = 0; j < have[i].size(); j += 2) {
            std::cout << have[i][j] << ' ' << have[i][j + 1] << '\n';
        }
    }
}

*/

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
