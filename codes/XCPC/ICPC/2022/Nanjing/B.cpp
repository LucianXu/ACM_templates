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
    int n, k;
    std::cin >> n >> k;
    vl a(n + 2);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::string s;
    std::cin >> s;
    s = "#" + s;

    // 不修改的情况, 单调队列优化 dp //
    std::deque<int> q;
    q.push_back(0);
    vl f(n + 2, INF);    // 前缀 dp 值 //
    f[0] = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (!q.empty() and i - q.front() >= k + 1) q.pop_front();
        Min(f[i], f[q.front()] + a[i]);
        while (!q.empty() and f[q.back()] >= f[i]) q.pop_back();
        if (s[i] == '1') q.clear();
        q.push_back(i);
    }
    q.clear();
    q.push_back(n + 1);
    vl g(n + 2, INF);    // 后缀 dp 值 //
    g[n + 1] = 0;
    for (int i = n; i >= 0; i--) {
        if (!q.empty() and q.front() - i >= k + 1) q.pop_front();
        Min(g[i], g[q.front()] + a[i]);
        while (!q.empty() and g[q.back()] >= g[i]) q.pop_back();
        if (s[i] == '1') q.clear();
        q.push_back(i);
    }

    int m;
    std::cin >> m;
    while (m--) {
        int pos;
        LL val, ans = INF;
        std::cin >> pos >> val;

        vl dp(2 * k + 2, INF);    // dp 修改后长度为 k 的段 //
        int le = std::max(0, pos - k), ri = pos - 1;
        for (int i = le; i <= ri; i++) dp[i - le] = f[i];
        std::deque<int> q;
        q.push_back(le);
        for (int i = le; i <= std::min(n + 1, ri + k + 2); i++) {
            if (!q.empty() and i - q.front() >= k + 1) q.pop_front();
            if (i == pos) {
                Min(dp[i - le], dp[q.front() - le] + val);
            } else if (i > pos) {
                Min(dp[i - le], dp[q.front() - le] + a[i]);
            }
            while (!q.empty() and dp[q.back() - le] >= dp[i - le]) q.pop_back();
            if (s[i] == '1') q.clear();
            q.push_back(i);
        }

        q.clear();
        q.push_back(le);
        for (int i = le; i <= pos; i++) {
            while (!q.empty() and dp[q.back() - le] >= dp[i - le]) q.pop_back();
            if (!q.empty() and i - q.front() >= k + 1) q.pop_front();
            if (s[i] == '1') q.clear();
            q.push_back(i);
        }
        for (int i = pos + 1; i <= std::min(n + 1, ri + k + 2); i++) {
            if (!q.empty() and i - q.front() >= k + 1) q.pop_front();
            Min(ans, dp[q.front() - le] + g[i]);
            if (s[i] == '1') q.clear();
            while (!q.empty() and dp[q.back() - le] >= dp[i - le]) q.pop_back();
            q.push_back(i);
        }
        std::cout << ans << '\n';
    }
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
