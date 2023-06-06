// created on lucian xu's laptop

#include <bits/stdc++.h>

// using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef std::pair<int, int> pii;
typedef std::pair<int, ll> pil;
typedef std::pair<ll, int> pli;
typedef std::pair<ll, ll> pll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;
typedef std::vector<pii> vpi;

#define typet typename t
#define typeu typename u
#define types typename... ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

#ifdef local
#include "debug.h"
#else
#define debug(...) \
    do {           \
    } while (false)
#endif

constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
constexpr int inf = 0x3f3f3f3f;
constexpr ll inf = 1e18;
constexpr double pi = 3.141592653589793;
constexpr double eps = 1e-6;

constexpr int lowbit(int x) { return x & -x; }
constexpr int add(int x, int y) { return x + y < mod ? x + y : x - mod + y; }
constexpr int sub(int x, int y) { return x < y ? mod + x - y : x - y; }
constexpr int mul(ll x, int y) { return x * y % mod; }
constexpr void add(int& x, int y) { x = add(x, y); }
constexpr void sub(int& x, int y) { x = sub(x, y); }
constexpr void mul(int& x, int y) { x = mul(x, y); }
constexpr int pow(int x, int y, int z = 1) {
    for (; y; y /= 2) {
        if (y & 1) mul(z, x);
        mul(x, x);
    }
    return z;
}
temps constexpr int add(ts... x) {
    int y = 0;
    (..., add(y, x));
    return y;
}
temps constexpr int mul(ts... x) {
    int y = 1;
    (..., mul(y, x));
    return y;
}

tandu bool max(t& x, const u& y) { return x < y ? x = y, true : false; }
tandu bool min(t& x, const u& y) { return x > y ? x = y, true : false; }


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        vi a(n + 1);
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }
        vi opt;
        for (int i = 1; i <= n; i++) {
            int x = a[i];
            while (x) {
                opt.push_back(x);
                x /= 2;
            }
        }
        std::sort(all(opt));
        opt.erase(unique(all(opt)), opt.end());
        auto get = [&](int a, int b) -> ll {
            // a -> b 的最小操作步数 //
            if (a <= b) return b - a;
            int cnt = 0;
            while (a / 2 >= b) {
                cnt++;
                a /= 2;
            }
            return std::min((ll) a - b, (ll) b - a / 2 + 1) + cnt;
        };
        ll ans = inf;
        for (auto y : opt) {
            vi sum(n + 1);
            ll res = 0;
            for (int i = 1; i <= n; i++) {
                int x = a[i];
                sum[i] = get(x, y);
                res += sum[i];
            }
            std::sort(rall(sum));
            for (int i = 0; i < m; i++) {
                res -= sum[i];
            }
            min(ans, res);
        }
        std::cout << ans << '\n';
    }
    return 0;
}
