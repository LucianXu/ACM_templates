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
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        vvi a(n + 1, vi(3));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                std::cin >> a[i][j];
            }
        }
        int ans = 0;
        std::vector<std::array<std::array<std::array<int, 3>, 201>, 201>> f(n + 2);
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= 200; j++) {
                for (int k = 1; k <= 200; k++) {
                    for (int l = 0; l < 3; l++) {
                        f[i][j][k][l] = 0;
                    }
                }
            }
        }
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= 200; j++) {
                for (int k = 1; k <= 200; k++) {
                    for (int l = 0; l < 3; l++) {
                        int x = l;
                        int y = (l + 1) % 3;
                        int z = (l + 2) % 3;    // x: 当前, y: 下一个, z: 下下个 //
                        int res = f[i][j][k][l];
                        res -= (j < 200 ? j : 0);
                        res -= (k < 200 ? k : 0);    // 200 算爆表, 太久没练能力归零 //
                        if (i == n + 1) {
                            Max(ans, res);
                            continue;
                        }
                        int jj = std::min(j + 1, 200);
                        int kk = std::min(k + 1, 200);
                        // 练 x //
                        Max(f[i + 1][jj][kk][x], res + a[i][x]);
                        // 练 y //
                        Max(f[i + 1][kk][1][y], res + a[i][y]);
                        // 练 z //
                        Max(f[i + 1][1][jj][z], res + a[i][z]);
                    }
                }
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}
