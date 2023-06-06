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
    LL sum, add;
    int st, act;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, q;
    std::cin >> n >> q;
    vi a(n + 1), st(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> st[i];
    }

    // segment tree //
    std::vector<node> tr(n * 4);

    auto push_up = [&](int u) -> void {
        node& rt = tr[u];
        node& ls = tr[u << 1];
        node& rs = tr[u << 1 | 1];
        rt.sum = ls.sum + rs.sum;
        rt.act = ls.act + rs.act;
    };

    auto push_down = [&](int u) -> void {
        if (tr[u].l == tr[u].r) return;
        node& rt = tr[u];
        node& ls = tr[u << 1];
        node& rs = tr[u << 1 | 1];
        ls.sum += (LL) ls.act * rt.add;
        rs.sum += (LL) rs.act * rt.add;
        ls.add += rt.add, rs.add += rt.add;
        rt.add = 0;
    };

    std::function<void(int, int, int)> build = [&](int u, int l, int r) {
        if (l == r) {
            if (st[l] == 1)
                tr[u] = {l, l, a[l], 0, 1, 1};
            else
                tr[u] = {l, l, a[l], 0, 0, 0};
            return;
        }
        tr[u] = {l, r, 0, 0, 0, 0};
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        push_up(u);
    };

    // 修改 x 位置的 st 值 //
    std::function<void(int, int, int)> modify1 = [&](int u, int x, int flag) {
        int l = tr[u].l, r = tr[u].r;
        if (l == r) {
            tr[u].add = 0;
            tr[u].st = flag;
            tr[u].act = flag;
            return;
        }
        push_down(u);
        int mid = (l + r) >> 1;
        if (x <= mid)
            modify1(u << 1, x, flag);
        else
            modify1(u << 1 | 1, x, flag);
        push_up(u);
    };

    // 修改 [ql, qr] += k //
    std::function<void(int, int, int, LL)> modify2 = [&](int u, int ql, int qr, int k) {
        debug(u);
        int l = tr[u].l, r = tr[u].r;
        if (ql <= l and r <= qr) {
            tr[u].sum += (LL) tr[u].act * k;
            tr[u].add += k;
            return;
        }
        push_down(u);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify2(u << 1, ql, qr, k);
        if (mid < qr) modify2(u << 1 | 1, ql, qr, k);
        push_up(u);
    };

    std::function<LL(int, int, int)> query = [&](int u, int ql, int qr) -> LL {
        debug(u);
        int l = tr[u].l, r = tr[u].r;
        if (ql <= l and r <= qr) {
            return tr[u].sum;
        }
        push_down(u);
        int mid = (l + r) >> 1;
        LL ans = 0;
        if (ql <= mid) ans += query(u << 1, ql, qr);
        if (mid < qr) ans += query(u << 1 | 1, ql, qr);
        return ans;
    };

    build(1, 1, n);

    while (q--) {
        int op, l, r, x;
        std::cin >> op;
        // debug(op);
        if (op == 1) {
            std::cin >> x;
            modify1(1, x, 0);
        } else if (op == 2) {
            std::cin >> x;
            modify1(1, x, 1);
        } else if (op == 3) {
            std::cin >> l >> r >> x;
            modify2(1, l, r, x);
        } else {
            std::cin >> l >> r;
            debug(l, r, op);
            std::cout << query(1, l, r) << '\n';
        }
    }

    return 0;
}
