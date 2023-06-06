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
using Z = Mint<1000000007>;

std::vector<Z> fac(200010), fac_inv(200010);

void solut() {
    int n, m, k;
    std::cin >> n >> m >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    Z tmp = inv(Z(k) - 1);
    Z p = Z(1), q = power(Z(k) - 1, m);
    Z ans = power(Z(k), m) - q;
    for (int i = 1; i <= n - 1; i++) {
        p *= Z(m + 1 - i);
        q *= tmp;
        ans -= p * fac_inv[i] * q;
    }
    std::cout << ans.val() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    fac[0] = Z(1);
    for (int i = 1; i <= 200000; i++) fac[i] = fac[i - 1] * i;
    fac_inv[200000] = inv(fac[200000]);
    for (int i = 199999; i >= 0; i--) fac_inv[i] = fac_inv[i + 1] * (i + 1);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
