// created on Lucian Xu's Laptop

#include <bits/stdc++.h>

// using namespace std;

#define typet typename T
#define typeu typename U
#define types typename... Ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

using UI = unsigned int;
using ULL = unsigned long long;
using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using PII = std::pair<int, int>;
using PIL = std::pair<int, LL>;
using PLI = std::pair<LL, int>;
using PLL = std::pair<LL, LL>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vl = std::vector<LL>;
using vvl = std::vector<vl>;
using vpi = std::vector<PII>;

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
tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

template <int P>
struct Mint {
    int v = 0;

    // reflection
    template <typet = int>
    constexpr operator T() const {
        return v;
    }

    // constructor //
    constexpr Mint() = default;
    template <typet>
    constexpr Mint(T x) : v(x % P) {}

    // io //
    friend std::istream& operator>>(std::istream& is, Mint& x) {
        LL y;
        is >> y;
        x = y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Mint x) { return os << x.v; }

    // comparision //
    friend constexpr bool operator==(Mint lhs, Mint rhs) { return lhs.v == rhs.v; }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) { return lhs.v != rhs.v; }
    friend constexpr bool operator<(Mint lhs, Mint rhs) { return lhs.v < rhs.v; }
    friend constexpr bool operator<=(Mint lhs, Mint rhs) { return lhs.v <= rhs.v; }
    friend constexpr bool operator>(Mint lhs, Mint rhs) { return lhs.v > rhs.v; }
    friend constexpr bool operator>=(Mint lhs, Mint rhs) { return lhs.v >= rhs.v; }

    // arithmetic //
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        return lhs.v + rhs.v <= P ? lhs.v + rhs.v : lhs.v - P + rhs.v;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        return lhs.v < rhs.v ? lhs.v + P - rhs.v : lhs.v - rhs.v;
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        return static_cast<LL>(lhs.v) * rhs.v % P;
    }
    constexpr Mint operator+=(Mint rhs) { return v = v + rhs; }
    constexpr Mint operator-=(Mint rhs) { return v = v - rhs; }
    constexpr Mint operator*=(Mint rhs) { return v = v * rhs; }
    friend constexpr Mint operator&(Mint lhs, Mint rhs) { return lhs.v & rhs.v; }
    friend constexpr Mint operator|(Mint lhs, Mint rhs) { return lhs.v | rhs.v; }
    friend constexpr Mint operator^(Mint lhs, Mint rhs) { return lhs.v ^ rhs.v; }
    friend constexpr Mint operator>>(Mint lhs, Mint rhs) { return lhs.v >> rhs.v; }
    friend constexpr Mint operator<<(Mint lhs, Mint rhs) { return lhs.v << rhs.v; }
    constexpr Mint operator&=(Mint rhs) { return v = v & rhs; }
    constexpr Mint operator|=(Mint rhs) { return v = v | rhs; }
    constexpr Mint operator^=(Mint rhs) { return v = v ^ rhs; }
    constexpr Mint operator>>=(Mint rhs) { return v = v >> rhs; }
    constexpr Mint operator<<=(Mint rhs) { return v = v << rhs; }
    friend constexpr Mint power(Mint a, Mint n) {
        Mint ans = 1;
        while (n) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
    friend constexpr Mint inv(Mint rhs) { return power(rhs, P - 2); }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) { return lhs * inv(rhs); }
    constexpr Mint operator/=(Mint rhs) { return v = v / rhs; }
};
using Z = Mint<998244353>;

struct node {
    int a, b, c, val, ans;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n, w, h, l;
        std::cin >> w >> h >> l;
        vi a = {w}, b = {h}, c = {l};
        std::cin >> n;

        std::vector<node> data = {{0, 0, 0, 0, 0}};
        std::map<std::array<int, 3>, int> mapple;

        auto addData = [&](int x, int y, int z, int k) {
            std::array<int, 3> t = {x, y, z};
            auto p = mapple.find(t);
            if (p != mapple.end()) {
                data[p->ss].val += k;
            } else {
                mapple[t] = data.size();
                data.push_back({x, y, z, k, 0});
            }
            a.push_back(x);
            b.push_back(y);
            c.push_back(z);
        };

        for (int i = 1, xl, yl, zl, xr, yr, zr; i <= n; i++) {
            std::cin >> xl >> yl >> zl >> xr >> yr >> zr;
            addData(xl, yl, zl, 1);
            addData(xr, yl, zl, -1);
            addData(xl, yr, zl, -1);
            addData(xl, yl, zr, -1);
            addData(xr, yr, zl, 1);
            addData(xl, yr, zr, 1);
            addData(xr, yl, zr, 1);
            addData(xr, yr, zr, -1);
        }
        addData(0, 0, 0, -1);
        addData(w, 0, 0, 1);
        addData(0, h, 0, 1);
        addData(0, 0, l, 1);
        addData(w, h, 0, -1);
        addData(w, 0, l, -1);
        addData(0, h, l, -1);
        addData(w, h, l, 1);

        std::sort(all(a));
        a.erase(unique(all(a)), a.end());
        std::sort(all(b));
        b.erase(unique(all(b)), b.end());
        std::sort(all(c));
        c.erase(unique(all(c)), c.end());

        for (int i = 1; i < (int) data.size(); i++) {
            int x = data[i].a, y = data[i].b, z = data[i].c;
            data[i].a = std::lower_bound(all(a), data[i].a) - a.begin() + 1;
            data[i].b = std::lower_bound(all(b), data[i].b) - b.begin() + 1;
            data[i].c = std::lower_bound(all(c), data[i].c) - c.begin() + 1;
        }
        int am = std::lower_bound(all(a), w) - a.begin() + 1;
        int bm = std::lower_bound(all(b), h) - b.begin() + 1;
        int cm = std::lower_bound(all(c), l) - c.begin() + 1;

        bool ok = 1;
        int cnt = data.size() - 1;

        std::sort(data.begin() + 1, data.begin() + cnt + 1, [&](node x, node y) {
            if (x.a != y.a) return x.a < y.a;
            if (x.b != y.b) return x.b < y.b;
            return x.c < y.c;
        });
        for (int i = 1; i <= cnt; i++) {
            if (data[i].a == data[i - 1].a and data[i].b == data[i - 1].b) {
                data[i].val += data[i - 1].val;
            }
        }

        std::sort(data.begin() + 1, data.begin() + cnt + 1, [&](node x, node y) {
            if (x.b != y.b) return x.b < y.b;
            if (x.c != y.c) return x.c < y.c;
            return x.a < y.a;
        });
        for (int i = 1; i <= cnt; i++) {
            if (data[i].b == data[i - 1].b and data[i].c == data[i - 1].c) {
                data[i].val += data[i - 1].val;
            }
        }

        std::sort(data.begin() + 1, data.begin() + cnt + 1, [&](node x, node y) {
            if (x.c != y.c) return x.c < y.c;
            if (x.a != y.a) return x.a < y.a;
            return x.b < y.b;
        });
        for (int i = 1; i <= cnt; i++) {
            if (data[i].c == data[i - 1].c and data[i].a == data[i - 1].a) {
                data[i].val += data[i - 1].val;
            }
        }

        for (int i = 1; i <= cnt; i++) {
            ok &= !data[i].val;
        }

        std::cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}

/*
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n, w, h, l;
        std::cin >> w >> h >> l;
        std::cin >> n;

        __int128 A = __int128(w) * h * l, B = 0;

        std::map<std::tuple<int, int, int>, int> cnt;
        cnt[{0, 0, 0}] = 1;
        cnt[{0, 0, l}] = 1;
        cnt[{0, h, 0}] = 1;
        cnt[{0, h, l}] = 1;
        cnt[{w, 0, 0}] = 1;
        cnt[{w, 0, l}] = 1;
        cnt[{w, h, 0}] = 1;
        cnt[{w, h, l}] = 1;
        for (int i = 0; i < n; i++) {
            int xl, yl, zl, xr, yr, zr;
            std::cin >> xl >> yl >> zl >> xr >> yr >> zr;
            cnt[{xl, yl, zl}] ^= 1;
            cnt[{xl, yl, zr}] ^= 1;
            cnt[{xl, yr, zl}] ^= 1;
            cnt[{xl, yr, zr}] ^= 1;
            cnt[{xr, yl, zl}] ^= 1;
            cnt[{xr, yl, zr}] ^= 1;
            cnt[{xr, yr, zl}] ^= 1;
            cnt[{xr, yr, zr}] ^= 1;
            B += __int128(xr - xl) * (yr - yl) * (zr - zl);
        }

        bool ok = A == B;
        for ([[maybe_unused]] const auto& [_, c] : cnt) {
            ok &= !c;
        }

        std::cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}
*/
