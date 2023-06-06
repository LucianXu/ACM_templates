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

const ULL P = 13331;

ULL quick(ULL a, ULL b) {
    ULL res = 1;
    while (b) {
        if (b & 1) res = res * a;
        b >>= 1;
        a *= a;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::string s, ss = "";
    std::cin >> s;
    int n, cnt = 0;
    int l = 0, r = s.size() - 1;
    for (; l <= r; l++, r--) {
        if (s[l] != s[r]) break;
        cnt++;
    }
    for (int i = l; i <= r; i++) ss += s[i];
    if (ss == std::string("")) {
        std::cout << 1 << ' ' << s.size() << '\n';
        return 0;
    }
    s = ss;
    n = s.size();
    std::vector<ULL> sum(n + 1), sumre(n + 2);

    for (ULL i = 1, M = 1; i <= n; i++, M *= P) sum[i] = sum[i - 1] + s[i - 1] * M;
    std::string t = s;
    reverse(all(t));
    for (ULL i = 1, M = 1; i <= n; i++, M *= P) sumre[i] = sumre[i - 1] + t[i - 1] * M;

    for (int i = 1; 2 * i <= n; i++) {
        int l = 1, r = i;
        int ll = n - i + 1, rr = n;
        if (quick(P, ll - 1) * sum[r] == (sum[rr] - sum[ll - 1]) &&
            sum[ll - 1] - sum[r] == sumre[ll - 1] - sumre[r]) {
            std::cout << l + cnt << ' ' << r + cnt << '\n';
            return 0;
        }
    }

    for (int i = 1; 2 * i <= n; i++) {
        int l = 1, r = i;
        int ll = i + 1, rr = 2 * i;
        if (quick(P, i) * sum[r] == sum[rr] - sum[ll - 1] &&
            quick(P, rr) * sumre[n - 2 * i] == sum[n] - sum[rr]) {
            std::cout << ll + cnt << ' ' << n + cnt << '\n';
            return 0;
        }
    }

    for (int i = 1; 2 * i <= n; i++) {
        int l = 1, r = i;
        int ll = i + 1, rr = 2 * i;
        if (quick(P, i) * sumre[r] == sumre[rr] - sumre[ll - 1] &&
            quick(P, rr) * sum[n - 2 * i] == sumre[n] - sumre[rr]) {
            std::cout << 1 + cnt << ' ' << n - i + cnt << '\n';
            return 0;
        }
    }

    std::cout << "-1 -1" << '\n';
    return 0;
}
