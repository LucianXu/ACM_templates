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

const ULL P = 13331;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<std::string> s(n + 1);
        vi final(n + 1);
        for (int i = 1; i <= n; i++) {
            std::cin >> s[i];
            std::cin >> final[i];
        }
        std::vector<std::vector<LL>> gongxian(4, std::vector<LL>(10));
        for (char c = 'A'; c <= 'D'; c++) {
            int i = c - 'A';
            for (int j = 0; j < 10; j++) {
                ULL res = 0, tot = 1;
                for (int k = 1; k <= n; k++) {
                    if (s[k][j] == c) res += tot * 10;
                    tot *= P;
                }
                gongxian[i][j] = res;
            }
        }

        ULL finalhash = 0, k = 1;
        for (int j = 1; j <= n; j++) finalhash += k * final[j], k *= P;

        std::map<ULL, int> mp;
        std::vector<char> ch(10);
        for (ch[0] = 'A'; ch[0] <= 'D'; ch[0]++) {
            for (ch[1] = 'A'; ch[1] <= 'D'; ch[1]++) {
                for (ch[2] = 'A'; ch[2] <= 'D'; ch[2]++) {
                    for (ch[3] = 'A'; ch[3] <= 'D'; ch[3]++) {
                        for (ch[4] = 'A'; ch[4] <= 'D'; ch[4]++) {
                            vi score(n + 1);
                            ULL res = 0, k = 1;

                            for (int j = 0; j < 5; j++) res += gongxian[ch[j] - 'A'][j];
                            mp[res]++;
                        }
                    }
                }
            }
        }

        LL ans = 0;

        for (ch[5] = 'A'; ch[5] <= 'D'; ch[5]++) {
            for (ch[6] = 'A'; ch[6] <= 'D'; ch[6]++) {
                for (ch[7] = 'A'; ch[7] <= 'D'; ch[7]++) {
                    for (ch[8] = 'A'; ch[8] <= 'D'; ch[8]++) {
                        for (ch[9] = 'A'; ch[9] <= 'D'; ch[9]++) {
                            vi score = final;
                            ULL res = finalhash, k = 1;

                            for (int j = 5; j < 10; j++) res -= gongxian[ch[j] - 'A'][j];
                            auto it = mp.find(res);
                            if (it != mp.end()) ans += it->ss;
                        }
                    }
                }
            }
        }

        std::cout << ans << '\n';
    }
    return 0;
}
