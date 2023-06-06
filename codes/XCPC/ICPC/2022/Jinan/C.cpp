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

    int n;
    std::cin >> n;
    vvi e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    vi fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);

    vi siz(n + 1);     // 子树大小 //
    vi tot(n + 1);     // 子树内部 dfs 序列数 //
    vvi son(n + 1);    // 子节点 //

    std::function<void(int, int)> dfs1 = [&](int u, int fa) {
        siz[u] = tot[u] = 1;
        for (auto v : e[u]) {
            if (v == fa) continue;
            son[u].push_back(v);
            dfs1(v, u);
            siz[u] += siz[v];
            Mul(tot[u], tot[v]);
        }
        Mul(tot[u], fac[son[u].size()]);
    };

    dfs1(1, 0);

    vvi dp(n + 1, vi(n + 1));
    dp[1][1] = tot[1];

    std::function<void(int)> dfs2 = [&](int u) {
        if (son[u].empty()) return;

        vvi f(n + 1, vi(n + 1));
        // f[i][j] 表示选择 i 个子树大小为 j 的方案数 //
        f[0][0] = 1;

        // 先做背包 //
        for (auto v : son[u]) {
            for (int i = son[u].size(); i >= 1; i--) {
                for (int j = siz[u]; j >= siz[v]; j--) {
                    Add(f[i][j], f[i - 1][j - siz[v]]);
                }
            }
        }

        // 枚举更新 u 的儿子 v //
        for (auto v : son[u]) {
            // 回退背包中 v 的贡献 //
            for (int i = 1; i <= son[u].size(); i++) {
                for (int j = siz[v]; j <= siz[u]; j++) {
                    Sub(f[i][j], f[i - 1][j - siz[v]]);
                }
            }

            // 计算 v 的兄弟排列的贡献 //
            vi g(n + 1);
            // g[j] 表示 v 在 u 的子树中 dfs 序为 j 的方案数 //
            for (int i = 0; i <= son[u].size() - 1; i++) {
                // v 前面有 i 个兄弟, 后面有 son[u] - 1 - i 个兄弟 //
                for (int j = 0; j <= siz[u]; j++) {
                    Add(g[j + 1], mul(fac[i], fac[son[u].size() - 1 - i], f[i][j]));
                }
            }

            // 答案 dp 值转移, 添加来着 u 的贡献 //
            for (int i = 1; i <= n; i++) {
                for (int j = 1; i + j <= n; j++) {
                    Add(dp[v][i + j], mul(dp[u][i], g[j]));
                }
            }

            // 撤销回退 //
            for (int i = son[u].size(); i >= 1; i--) {
                for (int j = siz[u]; j >= siz[v]; j--) {
                    Add(f[i][j], f[i - 1][j - siz[v]]);
                }
            }
        }

        // dfs 下去 //
        for (auto v : son[u]) {
            dfs2(v);
        }
    };

    dfs2(1);

    // 每一个节点还要单位化 //

    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            Add(sum, dp[i][j]);
        }
        sum = pow(sum, mod - 2);
        for (int j = 1; j <= n; j++) {
            std::cout << mul(dp[i][j], sum, tot[1]) << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
