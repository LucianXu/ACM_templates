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
        std::string s1, s2, s3, s4, s5;
        std::cin >> s1 >> s2 >> s3 >> s4 >> s5;
        if (s1[1] != s2[1] or s2[1] != s3[1] or s3[1] != s4[1] or s4[1] != s5[1]) {
            std::cout << "check" << '\n';
            continue;
        }
        auto op = [&](auto op, char ch, int t) -> int {
            if ('0' < ch and ch <= '9') {
                return ch - '0';
            } else if (ch == 'T') {
                return 10;
            } else if (ch == 'J') {
                return 11;
            } else if (ch == 'Q') {
                return 12;
            } else if (ch == 'K') {
                return 13;
            } else if (ch == 'A') {
                if (t == 1) {
                    return 14;
                } else {
                    return 1;
                }
            }
        };
        vi v;
        v.push_back(op(op, s1[0], 1));
        v.push_back(op(op, s2[0], 1));
        v.push_back(op(op, s3[0], 1));
        v.push_back(op(op, s4[0], 1));
        v.push_back(op(op, s5[0], 1));
        std::sort(all(v));
        int hand = std::max(op(op, s1[0], 1), op(op, s2[0], 1));
        int desk = std::max({op(op, s3[0], 1), op(op, s4[0], 1), op(op, s5[0], 1)});
        if (v[0] == 2 and v[1] == 3 and v[2] == 4 and v[3] == 5 and v[4] == 14) {
            if ((s1[0] == 'A' and s2[0] == '5') or (s2[0] == 'A' and s1[0] == '5')) {
                std::cout << "allin" << '\n';
            } else {
                std::cout << "check" << '\n';
            }
            continue;
        }
        bool flag = true;
        for (int i = 1; i <= 4; i++) {
            if (v[i] != v[i - 1] + 1) {
                std::cout << "check" << '\n';
                flag = false;
                break;
            }
        }
        if (flag == false) continue;
        if (hand >= 10 or hand > desk) {
            std::cout << "allin" << '\n';
        } else {
            std::cout << "check" << '\n';
        }
    }
    return 0;
}
