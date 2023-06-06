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

    LL n;
    std::cin >> n;
    std::array<std::array<std::map<LL, LL>, 4>, 20> dp = {};
    std::array<int, 19> x = {};
    [&]() {
        LL y = n;
        for (int i = 0; i < 19; i++) {
            x[i] = y % 10;
            y /= 10;
        }
    }();

    dp[0][0][1] = 1;
    for (int h = 0; h < 19; h++) {
        for (int i = 0; i < 4; i++) {
            for (auto [s, c] : dp[h][i]) {
                for (int d = 0; d < 10; d++) {
                    if (d) {
                        int u = d > x[h] or (d == x[h] and i & 2);
                        dp[h + 1][u * 2][i & 1 ? 0 : s * d] += c;
                    } else {
                        dp[h + 1][!x[h] * 2 & i | 1][s] += c;
                    }
                }
            }
        }
    }

    std::map<LL, LL> cache;
    std::function<LL(LL)> F = [&](LL x) -> LL {
        if (x < 10) {
            return x;
        }
        auto [it, ok] = cache.emplace(x, 0);
        if (ok) {
            LL y = 1;
            for (; x; x /= 10) {
                y *= x % 10;
            }
            it->ss = F(y);
        }
        return it->ss;
    };

    LL ans = 0;
    for (auto [s, c] : dp[19][0]) {
        // debug(s, c);
        ans += F(s) * c;
    }
    for (auto [s, c] : dp[19][1]) {
        // debug(s, c);
        ans += F(s) * c;
    }

    std::cout << ans - 1 << '\n';

    return 0;
}
