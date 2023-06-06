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
// constexpr int add(int x, int y) { return x + y < mod ? x + y : x - mod + y; }
constexpr int sub(int x, int y) { return x < y ? mod + x - y : x - y; }
constexpr int mul(LL x, int y) { return x * y % mod; }
// constexpr void Add(int& x, int y) { x = add(x, y); }
constexpr void Sub(int& x, int y) { x = sub(x, y); }
constexpr void Mul(int& x, int y) { x = mul(x, y); }
constexpr int pow(int x, int y, int z = 1) {
    for (; y; y /= 2) {
        if (y & 1) Mul(z, x);
        Mul(x, x);
    }
    return z;
}
// temps constexpr int add(Ts... x) {
//     int y = 0;
//     (..., Add(y, x));
//     return y;
// }
temps constexpr int mul(Ts... x) {
    int y = 1;
    (..., Mul(y, x));
    return y;
}

tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

/*

// 没看懂的神秘小做法 //

struct node {
    int id, x, y;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<node> a(q + 1);
    for (int i = 1, op; i <= q; i++) {
        std::cin >> op;
        a[i].id = i;
        if (op == 1) {
            std::cin >> a[i].x >> a[i].y;
        } else {
            std::cin >> a[i].x;
            a[i].y = -1;
        }
    }
    std::sort(a.begin() + 1, a.end(), [](node& a, node& b) {
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });
    vi pos(q + 1);
    for (int i = 1; i <= q; i++) {
        pos[a[i].id] = i;
    }
    const int block = 400;
    int r = (q + block - 1) / block;
    vvi p(r + 1, vi(n + 1));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= n; j++) {
            p[i][j] = j;
        }
    }
    std::sort(a.begin() + 1, a.end(), [](node& a, node& b) { return a.id < b.id; });
    static vi b(100010, -1);
    for (int i = 1; i <= q; i++) {
        if (a[i].y == -1) {
            int x = a[i].x;
            for (int j = 1; j <= r; j++) x = p[j][x];
            std::cout << x << '\n';
        } else {
            int u = (pos[i] + block - 1) / block;
            b[pos[i]] = a[i].x;
            for (int j = u * block; j > (u - 1) * block; j--) {
                int x = b[j];
                if (x == -1) continue;
                p[u][x] = x;
                p[u][x + 1] = x + 1;
            }
            for (int j = u * block; j > (u - 1) * block; j--) {
                int x = b[j];
                if (x == -1) continue;
                std::swap(p[u][x], p[u][x + 1]);
            }
        }
    }

    return 0;
}

*/


/*
嘿嘿下面这个也没看懂
自己写的线段树挂掉了
*/
struct node {
    node* ch[2];
    int l = 0, r = 0, cnt = 0;

    node(int _l, int _r) : l(_l), r(_r) {
        cnt = 0;
        ch[0] = ch[1] = NULL;
    }
};

void merge(node* a, node* b, int x) {
    int l = a->l, r = a->r;
    int mid = (l + r) >> 1;
    if (r <= x) return;

    if (a->ch[1] == NULL) a->ch[1] = new node(mid, r);
    if (b->ch[1] == NULL) b->ch[1] = new node(mid, r);
    if (x <= mid) {
        std::swap(a->ch[1], b->ch[1]);
        if (a->ch[0] == NULL) a->ch[0] = new node(l, mid);
        if (b->ch[0] == NULL) b->ch[0] = new node(l, mid);
        merge(a->ch[0], b->ch[0], x);
    } else {
        merge(a->ch[1], b->ch[1], x);
    }
}

void add(node* nd, int x) {
    int l = nd->l, r = nd->r;
    if (l + 1 == r) {
        nd->cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid <= x) {
        if (nd->ch[1] == NULL) nd->ch[1] = new node(mid, r);
        add(nd->ch[1], x);
    } else {
        if (nd->ch[0] == NULL) nd->ch[0] = new node(l, mid);
        add(nd->ch[0], x);
    }
}

std::vector<int> ans;
void query(node* nd, int col) {
    int l = nd->l, r = nd->r;
    if (l + 1 == r) {
        if (nd->cnt) {
            ans[nd->l] = col;
        }
    }
    if (nd->ch[0] != NULL) query(nd->ch[0], col);
    if (nd->ch[1] != NULL) query(nd->ch[1], col);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<vpi> upds(m + 2);
    vvi ori(n + 1);
    for (int i = 1, op; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            int a, b;
            std::cin >> a >> b;
            upds[b].push_back({a, i});
        } else {
            int a;
            std::cin >> a;
            ori[a].push_back(i);
        }
    }
    std::vector<node*> nds(n + 1);
    for (int i = 1; i <= n; i++) {
        nds[i] = new node(0, q + 2);
        for (auto id : ori[i]) add(nds[i], id);
    }
    for (int i = 1; i <= m + 1; i++) {
        for (auto [a, x] : upds[i]) {
            merge(nds[a], nds[a + 1], x);
        }
    }
    ans.resize(q + 1, -1);
    for (int i = 1; i <= n; i++) {
        query(nds[i], i);
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i] >= 0) std::cout << ans[i] << '\n';
    }
}
