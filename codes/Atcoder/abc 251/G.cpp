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
#define endl '\n'
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

tandu struct pnt {
    T x, y;

    pnt(T _x = 0, T _y = 0) { x = _x, y = _y; }

    pnt operator+(const pnt& a) const { return pnt(x + a.x, y + a.y); }

    pnt operator-(const pnt& a) const { return pnt(x - a.x, y - a.y); }

    /*
    bool operator<(const pnt& a) const {
        if (std::is_same<T, double>::value) {
            if (fabs(x - a.x) < eps) return y < a.y;
        } else {
            if (x == a.x) return y < a.y;
        }
        return x < a.x;
    }
    */

    // 注意数乘会不会爆 int //
    pnt operator*(const T k) const { return pnt(k * x, k * y); }

    U operator*(const pnt& a) const { return (U) x * a.x + (U) y * a.y; }

    U operator^(const pnt& a) const { return (U) x * a.y - (U) y * a.x; }

    U dist(const pnt a) { return ((U) a.x - x) * ((U) a.x - x) + ((U) a.y - y) * ((U) a.y - y); }

    U len() { return dist(pnt(0, 0)); }

    // a, b, c 成逆时针 //
    friend U area(pnt a, pnt b, pnt c) { return (b - a) ^ (c - a); }

    // 两向量夹角，返回 cos 值 //
    double get_angle(pnt a) {
        return (double) (pnt(x, y) * a) / sqrt((double) pnt(x, y).len() * (double) a.len());
    }
};

typedef pnt<LL, LL> point;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, q;
    std::cin >> n;
    std::vector<point> a(n + 1);
    vl areas(n + 1, -INF);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].x >> a[i].y;
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        point t;
        std::cin >> t.x >> t.y;
        for (int j = 1; j <= n; j++) {
            LL res = area(a[j], (j != n ? a[j + 1] : a[1]), a[j] + t);
            Max(areas[j], res);
        }
    }
    std::cin >> q;
    while (q--) {
        bool flag = true;
        point t;
        std::cin >> t.x >> t.y;
        for (int j = 1; j <= n; j++) {
            LL res = area(a[j], (j != n ? a[j + 1] : a[1]), t);
            if (res < areas[j]) {
                flag = false;
                break;
            }
        }
        std::cout << (flag ? "Yes" : "No") << endl;
    }

    return 0;
}
