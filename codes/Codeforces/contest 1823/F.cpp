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
    constexpr int val() const { return v; }
    constexpr int mod() { return P; }

    // io //
    friend std::istream& operator>>(std::istream& is, Mint& x) {
        LL y;
        is >> y;
        x = y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Mint x) { return os << x.v; }

    // comparision //
    friend constexpr bool operator==(const Mint& lhs, const Mint& rhs) { return lhs.v == rhs.v; }
    friend constexpr bool operator!=(const Mint& lhs, const Mint& rhs) { return lhs.v != rhs.v; }
    friend constexpr bool operator<(const Mint& lhs, const Mint& rhs) { return lhs.v < rhs.v; }
    friend constexpr bool operator<=(const Mint& lhs, const Mint& rhs) { return lhs.v <= rhs.v; }
    friend constexpr bool operator>(const Mint& lhs, const Mint& rhs) { return lhs.v > rhs.v; }
    friend constexpr bool operator>=(const Mint& lhs, const Mint& rhs) { return lhs.v >= rhs.v; }

    // arithmetic //
    template <typet>
    friend constexpr Mint power(Mint a, T n) {
        Mint ans = 1;
        while (n) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
    friend constexpr Mint inv(const Mint& rhs) { return power(rhs, P - 2); }
    friend constexpr Mint operator+(const Mint& lhs, const Mint& rhs) {
        return lhs.val() + rhs.val() < P ? lhs.val() + rhs.val() : lhs.val() - P + rhs.val();
    }
    friend constexpr Mint operator-(const Mint& lhs, const Mint& rhs) {
        return lhs.val() < rhs.val() ? lhs.val() + P - rhs.val() : lhs.val() - rhs.val();
    }
    friend constexpr Mint operator*(const Mint& lhs, const Mint& rhs) {
        return static_cast<LL>(lhs.val()) * rhs.val() % P;
    }
    friend constexpr Mint operator/(const Mint& lhs, const Mint& rhs) { return lhs * inv(rhs); }
    Mint operator+() const { return *this; }
    Mint operator-() const { return Mint() - *this; }
    constexpr Mint& operator++() {
        v++;
        if (v == P) v = 0;
        return *this;
    }
    constexpr Mint& operator--() {
        if (v == 0) v = P;
        v--;
        return *this;
    }
    constexpr Mint& operator++(int) {
        Mint ans = *this;
        ++*this;
        return ans;
    }
    constexpr Mint operator--(int) {
        Mint ans = *this;
        --*this;
        return ans;
    }
    constexpr Mint& operator+=(const Mint& rhs) {
        v = v + rhs;
        return *this;
    }
    constexpr Mint& operator-=(const Mint& rhs) {
        v = v - rhs;
        return *this;
    }
    constexpr Mint& operator*=(const Mint& rhs) {
        v = v * rhs;
        return *this;
    }
    constexpr Mint& operator/=(const Mint& rhs) {
        v = v / rhs;
        return *this;
    }
};
using Z = Mint<998244353>;

void solut() {
    int n, s, t;
    std::cin >> n >> s >> t;
    vvi e(n + 1);
    for (int i = 1, u, v; i <= n - 1; i++) {
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    // 树上随机游走 //
    std::vector<Z> f(n + 1);    // 向父亲走的期望距离 //
    std::vector<Z> g(n + 1);    // 向儿子走的期望距离 //

    auto dfs1 = [&](auto&& self, int u, int fa) -> void {
        f[u] = Z(e[u].size());
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            f[u] += f[v];
        }
    };

    auto dfs2 = [&](auto&& self, int u, int fa) -> void {
        if (u != s) g[u] = g[fa] + f[fa] - f[u];
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };

    dfs1(dfs1, s, 0);
    dfs2(dfs2, s, 0);

    debug(f);
    debug(g);
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
