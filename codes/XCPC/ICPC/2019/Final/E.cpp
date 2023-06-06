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
        int n, m, idx = 1;
        LL sum = 0, ans = 0;
        std::cin >> n >> m;
        if (n == 2) {
            std::cout << "0" << '\n';
            return 0;
        }
        vi fa(n + 1);
        std::iota(all(fa), 0);
        std::vector<std::tuple<int, int, int>> e;
        auto find = [&](auto find, int x) -> int {
            if (x == fa[x]) return x;
            return fa[x] = find(find, fa[x]);
        };
        vvi a(n + 1);
        std::map<int, int> mapple;
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            sum += w;
            e.push_back(std::make_tuple(u, v, w));
            if (u == 1) mapple[v] = idx++;
            if (u != 1 and v != n) fa[v] = find(find, u);
        }
        for (auto [u, v, w] : e) {
            if (v == n) {
                a[mapple[find(find, u)]].push_back(w);
            } else {
                a[mapple[find(find, v)]].push_back(w);
            }
        }
        for (int i = 1; i <= idx; i++) std::sort(all(a[i]));
        int k = a[1].size();
        sum /= k;
        for (int i = 0; i <= k - 1; i++) {
            LL flow = 0;
            for (int j = 1; j <= idx - 1; j++) {
                flow += 1LL * a[j][i];
            }
            if (flow < sum) ans += sum - flow;
        }
        std::cout << ans << '\n';
    }
    return 0;
}
