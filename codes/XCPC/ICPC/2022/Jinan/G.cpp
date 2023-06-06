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

struct node {
    int l, r;
    int maxx, minn;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n, ans = 0;
        std::cin >> n;
        vi a(n + 1);
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }

        // segment tree //
        std::vector<node> tr(n << 2);

        auto push_up = [&](int u) -> void {
            node& ro = tr[u];
            node& le = tr[u << 1];
            node& ri = tr[u << 1 | 1];
            ro.maxx = std::max(le.maxx, ri.maxx);
            ro.minn = std::min(le.minn, ri.minn);
        };

        std::function<void(int, int, int)> build = [&](int u, int l, int r) {
            if (l == r) {
                tr[u] = {l, l, a[l], a[l]};
                return;
            }
            tr[u].l = l, tr[u].r = r;
            int mid = (l + r) >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            push_up(u);
        };

        std::function<void(int, int, int)> modify = [&](int u, int pos, int val) {
            // pos 上的数改为 val //
            int l = tr[u].l, r = tr[u].r;
            if (l == r) {
                tr[u].maxx = val;
                tr[u].minn = val;
                a[pos] = val;
                return;
            }
            int mid = (l + r) >> 1;
            if (pos <= mid) {
                modify(u << 1, pos, val);
            } else {
                modify(u << 1 | 1, pos, val);
            }
            push_up(u);
        };

        auto opt = [&](PII& a, PII b) -> PII {
            a.ff = std::max(a.ff, b.ff);
            a.ss = std::min(a.ss, b.ss);
            return a;
        };

        std::function<int(int, int, int, int)> queryl = [&](int u, int ql, int qr, int val) -> int {
            // 查询 [ql ~ qr] 左侧第一个不小于 val 的值 //
            int l = tr[u].l, r = tr[u].r;
            if (l > qr or r < ql or tr[u].maxx < val) {
                return -1;
            }
            if (l == r) return l;
            int mid = (l + r) >> 1, p = -1;
            if (ql <= mid) p = queryl(u << 1, ql, qr, val);
            if (p == -1) p = queryl(u << 1 | 1, ql, qr, val);
            return p;
        };

        std::function<int(int, int, int, int)> queryr = [&](int u, int ql, int qr, int val) -> int {
            // 查询 [ql ~ qr] 右侧第一个不大于 val 的值 //
            int l = tr[u].l, r = tr[u].r;
            if (l > qr or r < ql or tr[u].minn > val) {
                return -1;
            }
            if (l == r) return l;
            int mid = (l + r) >> 1, p = -1;
            if (mid < qr) p = queryr(u << 1 | 1, ql, qr, val);
            if (p == -1) p = queryr(u << 1, ql, qr, val);
            return p;
        };

        auto partiton = [&](int l, int r) -> int {
            int p = a[(l + r) >> 1];
            int i = l - 1, j = r + 1;
            while (1) {
                i++, j--;
                int x = queryl(1, i, r, p);
                int y = queryr(1, l, j, p);
                if (x >= y) return y;
                int xx = a[x], yy = a[y];
                modify(1, x, yy);
                modify(1, y, xx);
                ans++;
                i = x, j = y;
            }
        };

        std::function<void(int, int)> quicksort = [&](int l, int r) {
            if (!l or !r or l >= r) return;
            int mid = partiton(l, r);
            quicksort(l, mid);
            quicksort(mid + 1, r);
        };

        build(1, 1, n);
        quicksort(1, n);

        std::cout << ans << '\n';
    }
    return 0;
}
