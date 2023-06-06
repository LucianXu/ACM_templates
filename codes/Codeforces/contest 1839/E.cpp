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

void solut() {
    int n;
    std::cin >> n;
    int sum = 0;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }
    if (~sum & 1) {
        // 背包 //
        vi f(sum / 2 + 1);
        vvi cases(sum / 2 + 1);
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int v = sum / 2; v >= a[i]; v--) {
                if (f[v - a[i]]) {
                    f[v] = f[v - a[i]];
                    cases[v] = cases[v - a[i]];
                    cases[v].push_back(i);
                }
            }
        }
        if (f[sum / 2]) {
            vi st(n + 1);
            for (const auto& x : cases[sum / 2]) st[x] = 1;
            std::cout << "Second" << '\n';
            while (1) {
                int x;
                std::cin >> x;
                if (x == 0) return;
                if (st[x] == 1) {
                    int y = 1;
                    for (y = 1; y <= n; y++) {
                        if (st[y] == 0 and a[y]) break;
                    }
                    std::cout << y << '\n';
                    int minn = std::min(a[x], a[y]);
                    a[x] -= minn, a[y] -= minn;
                } else {
                    int y = 1;
                    for (y = 1; y <= n; y++) {
                        if (st[y] == 1 and a[y]) break;
                    }
                    std::cout << y << '\n';
                    int minn = std::min(a[x], a[y]);
                    a[x] -= minn, a[y] -= minn;
                }
            }
        }
    }
    std::cout << "First" << '\n';
    while (1) {
        int y = 1;
        for (y = 1; y <= n; y++) {
            if (a[y]) break;
        }
        std::cout << y << '\n';

        int x;
        std::cin >> x;

        if (x == 0) return;
        int minn = std::min(a[x], a[y]);
        a[x] -= minn, a[y] -= minn;
    }
    return;
}

int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);
    // std::cout.tie(0);

    solut();

    return 0;
}
