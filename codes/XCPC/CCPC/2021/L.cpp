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

LL n, m, x, y;

LL get(std::vector<LL> temp) {
    LL last = 0;
    LL tot = 0;
    for (int i = 0; i < temp.size(); i++) {
        LL minn = std::min(x, y - last);
        debug(temp[i], minn);
        if (temp[i] <= minn)
            last = temp[i];
        else {
            tot++;
            temp[i] -= minn + 1;
            LL b = y - minn;
            LL a = minn;
            tot += temp[i] / (y + 2) * 2;
            temp[i] = temp[i] % (y + 2);
            if (temp[i] > b) temp[i] -= (b + 1), tot++;
            last = temp[i];
        }
    }
    return tot;
}

void solut() {
    std::cin >> n >> m >> x >> y;
    std::vector<LL> temp;
    LL beg = 1;
    temp.push_back(0);
    for (int i = 1; i <= m; i++) {
        LL p;
        std::cin >> p;
        temp.push_back(p - beg);
        beg = p + 1;
    }

    temp.push_back(n + 1 - beg);
    LL ans = INF;
    Min(ans, get(temp));
    reverse(all(temp));
    Min(ans, get(temp));
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
