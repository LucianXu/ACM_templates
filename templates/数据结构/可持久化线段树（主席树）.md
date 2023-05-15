# 可持久化线段树（主席树）

## 第 $1$ 个例题

$n$ 个数，$m$ 次操作，操作分别为

1. $v_i \ 1 \ loc_i \ value_i$：将第 $v_i$ 个版本的 $a[loc_i]$ 修改为 $value_i$
2. $v_i \ 2 \ loc_i$：拷贝第 $v_i$ 个版本，并查询该版本的 $a[loc_i]$

```cpp
// 洛谷 P3919 【模板】可持久化线段树 1（可持久化数组）

struct node {
    int l, r, key;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    // hjt segment tree //
    int idx = 0;
    vi root(m + 1);
    std::vector<node> tr(n * 25);

    std::function<int(int, int)> build = [&](int l, int r) -> int {
        int p = ++idx;
        if (l == r) {
            tr[p].key = a[l];
            return p;
        }
        int mid = (l + r) >> 1;
        tr[p].l = build(l, mid);
        tr[p].r = build(mid + 1, r);
        return p;
    };

    std::function<int(int, int, int, int, int)> modify = [&](int p, int l, int r, int k,
                                                             int x) -> int {
        int q = ++idx;
        tr[q].l = tr[p].l, tr[q].r = tr[p].r;
        if (tr[q].l == tr[q].r) {
            tr[q].key = x;
            return q;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            tr[q].l = modify(tr[q].l, l, mid, k, x);
        } else {
            tr[q].r = modify(tr[q].r, mid + 1, r, k, x);
        }
        return q;
    };

    std::function<int(int, int, int, int)> query = [&](int p, int l, int r, int k) -> int {
        if (tr[p].l == tr[p].r) {
            return tr[p].key;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            return query(tr[p].l, l, mid, k);
        } else {
            return query(tr[p].r, mid + 1, r, k);
        }
    };

    root[0] = build(1, n);

    for (int i = 1; i <= m; i++) {
        int op, ver, k, x;
        std::cin >> ver >> op;
        if (op == 1) {
            std::cin >> k >> x;
            root[i] = modify(root[ver], 1, n, k, x);
        } else {
            std::cin >> k;
            root[i] = root[ver];
            std::cout << query(root[ver], 1, n, k) << endl;
        }
    }

    return 0;
}
```

指针写法

（可惜洛谷上 $\#2$ 点会 $MLE$，更新数据后变成 $TLE$ 了）

```cpp
int n, m, k, x, vi, op, a[N];

struct node {
    node *ch[2];
    int key;

    node() {
        key = 0;
        ch[0] = ch[1] = nullptr;
    }

    node(node *_node) {
        key = _node->key;
        ch[0] = _node->ch[0], ch[1] = _node->ch[1];
    }
};

struct segment_tree {
    node *root[N];

    node *build(int l, int r) {
        node *new_node;
        new_node = new node();
        if (l == r) {
            new_node->key = a[l];
            return new_node;
        }
        int mid = (l + r) >> 1;
        new_node->ch[0] = build(l, mid);
        new_node->ch[1] = build(mid + 1, r);
        return new_node;
    }

    // a[k] 改成 x //
    node *modify(node *p, int l, int r, int k, int x) {
        node *new_node;
        new_node = new node(p);
        if (l == r) {
            new_node->key = x;
            return new_node;
        }
        int mid = (l + r) >> 1;
        if (k <= mid)
            new_node->ch[0] = modify(new_node->ch[0], l, mid, k, x);
        else
            new_node->ch[1] = modify(new_node->ch[1], mid + 1, r, k, x);
        return new_node;
    }

    // 询问 p 为根节点的版本的 a[k] //
    int query(node *p, int l, int r, int k) {
        if (l == r) {
            return p->key;
        }
        int mid = (l + r) >> 1;
        if (k <= mid)
            return query(p->ch[0], l, mid, k);
        else
            return query(p->ch[1], mid + 1, r, k);
    }
};

segment_tree tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    tr.root[0] = tr.build(1, n);
    rep(i, 1, m) {
        cin >> vi >> op;
        if (op == 1) {
            cin >> k >> x;
            tr.root[i] = tr.modify(tr.root[vi], 1, n, k, x);
        } else {
            cin >> k;
            tr.root[i] = tr.root[vi];
            cout << tr.query(tr.root[vi], 1, n, k) << endl;
        }
    }
    return 0;
}
```

## 第 $2$ 个例题

长度为 $n$ 的序列 $a$，$m$ 次查询，每次查询 $[l, r]$ 中的第 $k$ 小值

```cpp
// 洛谷P3834 【模板】可持久化线段树 2

struct node {
    int l, r, cnt;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;
    vi a(n + 1), v;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        v.push_back(a[i]);
    }
    std::sort(all(v));
    v.erase(unique(all(v)), v.end());
    auto find = [&](int x) -> int { return std::lower_bound(all(v), x) - v.begin() + 1; };

    // hjt segment tree //
    std::vector<node>(n * 25);
    vi root(n + 1);
    int idx = 0;

    std::function<int(int, int)> build = [&](int l, int r) -> int {
        int p = ++idx;
        if (l == r) return p;
        int mid = (l + r) >> 1;
        tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
        return p;
    };

    std::function<int(int, int, int, int)> modify = [&](int p, int l, int r, int x) -> int {
        int q = ++idx;
        tr[q] = tr[p];
        if (tr[q].l == tr[q].r) {
            tr[q].cnt++;
            return q;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            tr[q].l = modify(tr[q].l, l, mid, x);
        } else {
            tr[q].r = modify(tr[q].r, mid + 1, r, x);
        }
        tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
        return q;
    };

    std::function<int(int, int, int, int, int)> query = [&](int p, int q, int l, int r,
                                                            int x) -> int {
        if (l == r) return l;
        int cnt = tr[tr[p].l].cnt - tr[tr[q].l].cnt;
        int mid = (l + r) >> 1;
        if (x <= cnt) {
            return query(tr[p].l, tr[q].l, l, mid, x);
        } else {
            return query(tr[p].r, tr[q].r, mid + 1, r, x - cnt);
        }
    };

    root[0] = build(1, v.size());


    for (int i = 1; i <= n; i++) {
        root[i] = modify(root[i - 1], 1, v.size(), find(a[i]));
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << v[query(root[r], root[l - 1], 1, v.size(), k) - 1] << endl;
    }

    return 0;
}
```

指针写法

```cpp
int n, m, a[N];
vector<int> v;

int find(int x) { return lower_bound(all(v), x) - v.begin() + 1; }

struct node {
    node *ch[2];
    int cnt;

    node() {
        cnt = 0;
        ch[0] = ch[1] = nullptr;
    }

    node(node *_node) {
        cnt = _node->cnt;
        ch[0] = _node->ch[0], ch[1] = _node->ch[1];
    }
};

struct segment_tree {
    node *root[N];

    node *build(int l, int r) {
        node *new_node;
        new_node = new node();
        if (l == r) {
            return new_node;
        }
        int mid = (l + r) >> 1;
        new_node->ch[0] = build(l, mid);
        new_node->ch[1] = build(mid + 1, r);
        return new_node;
    }

    node *modify(node *p, int l, int r, int x) {
        node *new_node;
        new_node = new node(p);
        if (l == r) {
            new_node->cnt++;
            return new_node;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            new_node->ch[0] = modify(new_node->ch[0], l, mid, x);
        else
            new_node->ch[1] = modify(new_node->ch[1], mid + 1, r, x);
        new_node->cnt = new_node->ch[0]->cnt + new_node->ch[1]->cnt;
        return new_node;
    }

    int query(node *p, node *q, int l, int r, int x) {
        if (l == r) {
            return l;
        }
        int cnt = p->ch[0]->cnt - q->ch[0]->cnt;
        int mid = (l + r) >> 1;
        if (x <= cnt)
            return query(p->ch[0], q->ch[0], l, mid, x);
        else
            return query(p->ch[1], q->ch[1], mid + 1, r, x - cnt);
    }
};

segment_tree tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    rep(i, 1, n) {
        cin >> a[i];
        v.p_b(a[i]);
    }

    sort(all(v));
    v.erase(unique(all(v)), v.end());

    tr.root[0] = tr.build(1, v.size());
    rep(i, 1, n) { tr.root[i] = tr.modify(tr.root[i - 1], 1, v.size(), find(a[i])); }
    rep(i, 1, m) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << v[tr.query(tr.root[r], tr.root[l - 1], 1, v.size(), k) - 1] << endl;
    }
    return 0;
}

```

# UPDATE

## 2022.11.17

增加例题题号。