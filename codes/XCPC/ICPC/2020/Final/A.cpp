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

    std::string s;
    std::cin >> s;
    int n = s.size();
    s = "#" + s;
    auto get = [&](char ch) -> int {
        if ('0' <= ch and ch <= '9')
            return ch - '0' + 1;
        else if ('a' <= ch and ch <= 'z')
            return ch - 'a' + 11;
        else if ('A' <= ch and ch <= 'Z')
            return ch - 'A' + 37;
    };
    vi dp1(n + 1), last(70), sum1(70);
    vvi dp2(n + 1, vi(70)), dp3(n + 1, vi(70)), dp4(n + 1, vi(70));
    vvi sum2(70, vi(70)), sum3(70, vi(70));
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int d = get(s[i]);
        dp1[i] = add(dp1[last[d]], 1);
        for (int c = 1; c <= 62; c++) {
            if (c == d) continue;
            dp2[i][c] = add(dp1[last[c]], sum2[d][c]);
            dp3[i][c] = add(dp2[last[c]][d], sum3[d][c]);
            dp4[i][c] = dp3[last[c]][d];
            sum2[d][c] = dp2[i][c];
            sum3[d][c] = dp3[i][c];
        }
        last[d] = i;
    }
    auto C = [&](int x) -> int { return mul(x, x - 1, inv2); };
    int sum = 0, summ = 0;
    for (int i = 1; i <= n; i++) {
        int d = get(s[i]);
        for (int c = 1; c <= 62; c++) {
            if (c == d) continue;
            Add(ans,
                mul(add(sub(C(sum - sum1[c] - sum1[d]), summ), C(sum1[c]), C(sum1[d])), dp4[i][c]));
        }
        Sub(summ, C(sum1[d]));
        sum1[d]++, sum++;
        Add(summ, C(sum1[d]));
    }
    std::cout << ans << '\n';

    return 0;
}
