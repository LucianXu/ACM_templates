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
    int n, m, k;
    std::string s;
    std::cin >> n >> m >> k >> s;
    int u = 1, d = n, l = 1, r = m;
    int uu = 1, dd = n, ll = 1, rr = m;
    for (const auto& ch : s) {
        if (ch == 'U') {
            uu++, dd++;
        } else if (ch == 'D') {
            uu--, dd--;
        } else if (ch == 'L') {
            ll++, rr++;
        } else {
            ll--, rr--;
        }
        Max(u, uu), Min(d, dd), Max(l, ll), Min(r, rr);
    }
    if ((u > d or l > r)) {
        if (k != 0) {
            std::cout << '0' << '\n';
        } else {
            std::cout << n * m << '\n';
        }
        return;
    }
    vpi hole = {{0, 0}};
    int x = 0, y = 0;
    for (const auto& ch : s) {
        if (ch == 'U') {
            x++;
        } else if (ch == 'D') {
            x--;
        } else if (ch == 'L') {
            y++;
        } else {
            y--;
        }
        hole.push_back({x, y});
    }
    std::sort(all(hole));
    hole.erase(unique(all(hole)), hole.end());

    vvi a(4 * n + 2, vi(4 * m + 2));
    for (const auto& p : hole) {
        a[p.ff + 2 * n][p.ss + 2 * m] = 1;
    }
    for (int i = 4 * n; i >= 1; i--) {
        for (int j = 4 * m; j >= 1; j--) {
            a[i][j] += a[i + 1][j] + a[i][j + 1] - a[i + 1][j + 1];
        }
    }
    int res = (r - l + 1) * (d - u + 1);
    int ans = 0;
    for (int i = 2 * n; i >= n + 1; i--) {
        for (int j = 2 * m; j >= m + 1; j--) {
            int cnt = a[i + u - 1][j + l - 1] - a[i + d][j + l - 1] - a[i + u - 1][j + r] +
                      a[i + d][j + r];
            if (cnt == res - k) ans++;
        }
    }
    std::cout << ans << '\n';
}

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
