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
        std::string s;
        std::cin >> s;
        int n = s.size();
        auto z_function = [&](const std::string& s) -> vi {
            vi z(n);
            for (int i = 1, l = 0, r = 0; i < n; i++) {
                if (i <= r and z[i - l] < r - i + 1) {
                    z[i] = z[i - l];
                } else {
                    z[i] = std::max(0, r - i + 1);
                    while (z[i] + i < n and s[z[i]] == s[z[i] + i]) z[i]++;
                }
                if (z[i] + i - 1 > r) {
                    l = i;
                    r = z[i] + i - 1;
                }
            }
            return z;
        };
        vi z = z_function(s);

        // ST //
        vvi v(n + 1, vi(30));
        vi Log2(n + 1);
        auto ST_init = [&]() -> void {
            Log2[1] = 0;
            for (int i = 0; i <= n; i++) {
                v[i][0] = z[i];
                if (i > 1) Log2[i] = Log2[i / 2] + 1;
            }
            int t = Log2[(n + 1) / 2] + 1;
            for (int j = 1; j <= t; j++) {
                for (int i = 0; i <= n - (1 << j) + 1; i++) {
                    v[i][j] = std::max(v[i][j - 1], v[i + (1 << (j - 1))][j - 1]);
                }
            }
        };
        ST_init();

        auto query = [&](int l, int r) -> int {
            int t = Log2[r - l + 1];
            return std::max(v[l][t], v[r - (1 << t) + 1][t]);
        };

        vvi be(n + 1);
        for (int i = 1; i <= n; i++) {
            int l = i, r = n, le = l;
            while (l != n) {
                if (l >= n) break;
                debug(l, r);
                if (z[l] >= i) {
                    be[i].push_back(l + i - 1);
                    l = l + i;
                    r = n;
                } else {
                    le = l;
                    while (l + 1 != r) {
                        int mid = (l + r) >> 1;
                        if (query(le, mid) < i) {
                            l = mid;
                        } else {
                            r = mid;
                        }
                    }
                    if (r != n) {
                        be[i].push_back(r + i - 1);
                    }
                    l = r + i;
                    r = n;
                }
            }
        }

        // dp //
        vi f(n);
        std::iota(all(f), 1);
        for (int i = 1; i < n; i++) {
            Min(f[i], f[i - 1] + 1);
            for (int j = 0; j < (int) be[i].size(); j++) {
                int l = i - 1;
                int r = be[i][j];
                Min(f[r], f[l] + 1 + r - l - (j + 1) * l);
            }
        }
        std::cout << f[n - 1] << '\n';

        /* MAOoo 的做法
        std::set<int> pos;
        vvi rem(n);
        for (int i = 1; i < n; i++) {
            if (z[i]) {
                pos.insert(i);
                rem[z[i]].push_back(i);
            }
        }
        pos.insert(n);

        // dp //
        vi f(n);
        std::iota(all(f), 1);
        for (int i = 1; i < n; i++) {
            Min(f[i], f[i - 1] + 1);
            for (const auto& p : rem[i - 1]) {
                pos.erase(p);
            }
            for (int j = 1, p = i; p < n; j++, p += i) {
                p = *pos.lower_bound(p);
                if (p == n) break;
                int l = i - 1, r = p + i - 1;
                Min(f[r], f[l] + 1 + r - l - j * l);
            }
        }
        std::cout << f[n - 1] << '\n';
        */
    }
    return 0;
}
