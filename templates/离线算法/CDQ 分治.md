# CDQ 分治

$n$ 个三维数对 $(a_i, b_i, c_i)$，设 $f(i)$ 表示 $a_j \leqslant a_i$ 且 $b_j \leqslant b_i$ 且  $c_j \leqslant c_i$ 且 $i \neq j$ 的个数。输出 $f(i) \ (0 \leqslant i \leqslant n - 1)$  的值。

```cpp
// 洛谷 P3810 【模板】三维偏序（陌上花开）

struct data {
    int a, b, c, cnt, ans;

    data(int _a = 0, int _b = 0, int _c = 0, int _cnt = 0, int _ans = 0) {
        a = _a, b = _b, c = _c, cnt = _cnt, ans = _ans;
    }

    bool operator!=(data x) {
        if (a != x.a) return true;
        if (b != x.b) return true;
        if (c != x.c) return true;
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);


    int n, k;
    std::cin >> n >> k;
    static data v1[N], v2[N];
    for (int i = 1; i <= n; i++) {
        std::cin >> v1[i].a >> v1[i].b >> v1[i].c;
    }

    std::sort(v1 + 1, v1 + n + 1, [&](data x, data y) {
        if (x.a != y.a) return x.a < y.a;
        if (x.b != y.b) return x.b < y.b;
        return x.c < y.c;
    });

    int t = 0, top = 0;
    for (int i = 1; i <= n; i++) {
        t++;
        if (v1[i] != v1[i + 1]) {
            v2[++top] = v1[i];
            v2[top].cnt = t;
            t = 0;
        }
    }

    // BIT //
    vi tr(N);

    auto add = [&](int pos, int val) -> void {
        while (pos <= k) {
            tr[pos] += val;
            pos += lowbit(pos);
        }
    };

    auto query = [&](int pos) -> int {
        int ans = 0;
        while (pos > 0) {
            ans += tr[pos];
            pos -= lowbit(pos);
        }
        return ans;
    };

    std::function<void(int, int)> CDQ = [&](int l, int r) -> void {
        if (l == r) return;
        int mid = (l + r) >> 1;
        CDQ(l, mid), CDQ(mid + 1, r);
        std::sort(v2 + l, v2 + mid + 1, [&](data x, data y) {
            if (x.b != y.b) return x.b < y.b;
            return x.c < y.c;
        });
        std::sort(v2 + mid + 1, v2 + r + 1, [&](data x, data y) {
            if (x.b != y.b) return x.b < y.b;
            return x.c < y.c;
        });
        int i = l, j = mid + 1;
        while (j <= r) {
            while (i <= mid && v2[i].b <= v2[j].b) {
                add(v2[i].c, v2[i].cnt);
                i++;
            }
            v2[j].ans += query(v2[j].c);
            j++;
        }
        for (int ii = l; ii < i; ii++) {
            add(v2[ii].c, -v2[ii].cnt);
        }
        return;
    };

    CDQ(1, top);
    vi ans(n + 1);
    for (int i = 1; i <= top; i++) {
        ans[v2[i].ans + v2[i].cnt] += v2[i].cnt;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << endl;
    }

    return 0;
}
```

