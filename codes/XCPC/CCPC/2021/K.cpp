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
// #define endl '\n'
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
    std::cin >> t;
    while (t--) {
        LL n, m;
        std::cin >> n >> m;

        // 特判 1 //
        if (n == 1 or m == 1) {
            if (n == 1 and m == 1) {
                std::cout << 1 << '\n';
            } else if (n == 1) {
                std::cout << add(2, mul(m - 2, m - 3, inv2)) << '\n';
            } else {
                std::swap(n, m);
                std::cout << add(2, mul(m - 2, m - 3, inv2)) << '\n';
            }
            continue;
        }

        // 特判 2 //
        if (n == 2 or m == 2) {
            if (n == 2 and m == 2) {
                std::cout << 4 << '\n';
            } else if (n == 2) {
                std::cout << add(4, mul(m - 2, m - 3), mul(m - 2, m - 2)) << '\n';
            } else {
                std::swap(n, m);
                std::cout << add(4, mul(m - 2, m - 3), mul(m - 2, m - 2)) << '\n';
            }
            continue;
        }

        // 其他 //

        int ans = 0;

        // 1 个 //

        Add(ans, 4);

        // 2 个 //

        Add(ans, mul(n - 2, n - 2));
        Add(ans, mul(m - 2, m - 2));
        Add(ans, mul(n - 2, n - 3));
        Add(ans, mul(m - 2, m - 3));

        // 4 个 //

        int k = mul(n - 2, m - 2);
        Add(ans, mul(k, sub(k, 1), sub(k, 2), sub(k, 3), pow(24, mod - 2)));

        // 3 个 //

        Add(ans, mul(4, n - 2, n - 2, m - 2, m - 2));

        Add(ans, mul(n - 2, k, sub(k, 1)));
        Add(ans, mul(m - 2, k, sub(k, 1)));

        if (n >= 7) {
            Sub(ans, mul(m - 2, m - 2, n - 4, n - 5, n - 6, pow(3, mod - 2)));
        }
        if (m >= 7) {
            Sub(ans, mul(n - 2, n - 2, m - 4, m - 5, m - 6, pow(3, mod - 2)));
        }

        std::cout << ans << '\n';
    }
    return 0;
}
