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

    vvi a(31, vi(31));
    for (int k = 1; k <= 23; k += 2) {
        for (int i = k; i <= k + 2; i++) {
            for (int j = k; j <= k + 2; j++) {
                a[i][j] = 1;
            }
        }
    }
    for (int k = 1; k <= 30; k++) {
        a[30][k] = a[k][30] = 1;
    }

    int n;
    std::cin >> n;
    vi v = {0};
    while (n) {
        v.push_back(n % 6);
        n /= 6;
    }
    v.resize(15);
    debug(v);
    auto patten1 = [&](int x, int type) {
        if (type == 0) return;
        for (int i = x; i <= 30; i++) a[i][x] = 1;
        if (type == 1) {
            ;
        } else if (type == 2) {
            a[29][x + 1] = 1;
        } else if (type == 3) {
            a[28][x + 1] = 1;
            a[29][x + 1] = 1;
        } else if (type == 4) {
            a[27][x + 1] = 1;
            a[28][x + 1] = 1;
            a[29][x + 1] = 1;
        } else {
            a[28][x + 1] = 1;
            a[29][x + 1] = 1;
            a[29][x + 2] = 1;
        }
    };

    auto patten2 = [&](int x, int type) {
        if (type == 0) return;
        for (int i = x; i <= 30; i++) a[x][i] = 1;
        if (type == 1) {
            ;
        } else if (type == 2) {
            a[x + 1][29] = 1;
        } else if (type == 3) {
            a[x + 1][28] = 1;
            a[x + 1][29] = 1;
        } else if (type == 4) {
            a[x + 1][27] = 1;
            a[x + 1][28] = 1;
            a[x + 1][29] = 1;
        } else {
            a[x + 1][28] = 1;
            a[x + 1][29] = 1;
            a[x + 2][29] = 1;
        }
    };

    for (int k = 1; k <= 12; k++) {
        if (k & 1) {
            // down //
            patten1(2 * k - 1, v[k]);
        } else {
            patten2(2 * k - 1, v[k]);
        }
    }
    std::cout << 30 << '\n';
    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 30; j++) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
