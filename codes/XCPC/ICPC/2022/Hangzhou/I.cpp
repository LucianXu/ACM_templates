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

std::mt19937 rnd(std::random_device{}());

int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);
    // std::cout.tie(0);

    auto query = [&](int x) -> int {
        std::cout << "walk " << x << '\n';
        int ans;
        std::cin >> ans;
        return ans;
    };

    auto answer = [&](int x) { std::cout << "guess " << x << '\n'; };

    int maxx = 0;
    for (int i = 1; i <= 3000; i++) {
        Max(maxx, query(rnd() % 1000000000));
    }
    vi v;
    for (int i = 1; i <= 3000; i++) {
        v.push_back(query(1));
        if (i > 1 and v[0] == v.back()) {
            answer(v.size() - 1);
            return 0;
        }
    }
    int ans = query(maxx);
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == ans) {
            answer(maxx + v.size() - i - 1);
            return 0;
        }
    }
    for (int i = 1; i <= 3000; i++) {
        ans = query(3000);
        for (int j = 0; j < v.size(); j++) {
            if (v[j] == ans) {
                answer(maxx + v.size() - j - 1 + 3000 * i);
                return 0;
            }
        }
    }

    return 0;
}
