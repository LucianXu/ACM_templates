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
        int n;
        std::cin >> n;
        vl a(n + 1), b(n + 1);
        std::vector<bool> vis(n + 1);
        for (int i = 1; i <= n; i++) std::cin >> a[i];
        for (int i = 1; i <= n; i++) std::cin >> b[i];
        LL ans = 0;

        auto check = [&](auto check, LL x, LL y) -> bool {
            LL z = x;
            while (z <= y) {
                z *= x;
                if (z == y) return true;
            }
            return false;
        };

        for (int i = 2; i <= n; i++) {
            if (vis[i]) continue;
            vi v;
            for (LL j = i; j <= n; j *= i) {
                v.push_back((int) j);
                vis[j] = true;
            }
            LL maxx = 0;
            for (int op = 0; op < (1 << v.size()); op++) {
                LL ans1 = 0;

                for (int k = 0; k < v.size(); k++) {
                    if (op & (1 << k)) {
                        ans1 += a[v[k]];
                    }
                }
                for (int k = 0; k < v.size(); k++) {
                    for (int l = 0; l < v.size(); l++) {
                        if ((op & (1 << k)) and (op & (1 << l))) {
                            if (v[k] < v[l] and check(check, v[k], v[l]) == true) ans1 -= b[v[l]];
                        }
                    }
                }
                maxx = std::max(maxx, ans1);
            }
            ans += maxx;
        }
        std::cout << ans + a[1] << '\n';
    }
    return 0;
}
