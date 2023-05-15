# Treap（普通平衡树）

## 旋转Treap

$n$ 次操作，操作分为如下 $6$ 种：

1. 插入数 $x$
2. 删除数 $x$（若有多个相同的数，只删除一个）
3. 查询数 $x$ 的排名（排名定义为小于 $x$ 的数的个数 $+$ $1$）
4. 查询排名为 $x$ 的数
5. 求 $x$ 的前驱（前驱定义为小于 $x$ 的最大数）
6. 求 $x$ 的后继（后继定义为大于 $x$ 的最小数）

```cpp
// Problem: P3369 【模板】普通平衡树

int n, root, idx;

struct node {
    int l, r;
    int key, val;
    int cnt, size;
} treap[N];

void push_up(int p) {
    treap[p].size = treap[treap[p].l].size + treap[treap[p].r].size + treap[p].cnt;
}

int get_node(int key) {
    treap[++idx].key = key;
    treap[idx].val = rand();
    treap[idx].cnt = treap[idx].size = 1;
    return idx;
}

void zig(int &p) {
    // 右旋 //
    int q = treap[p].l;
    treap[p].l = treap[q].r, treap[q].r = p, p = q;
    push_up(treap[p].r), push_up(p);
}

void zag(int &p) {
    // 左旋 //
    int q = treap[p].r;
    treap[p].r = treap[q].l, treap[q].l = p, p = q;
    push_up(treap[p].l), push_up(p);
}

void build() {
    get_node(-inf), get_node(inf);
    root = 1, treap[1].r = 2;
    push_up(root);
    if (treap[1].val < treap[2].val) zag(root);
}

void insert(int &p, int key) {
    if (!p) {
        p = get_node(key);
    } else if (treap[p].key == key) {
        treap[p].cnt++;
    } else if (treap[p].key > key) {
        insert(treap[p].l, key);
        if (treap[treap[p].l].val > treap[p].val) zig(p);
    } else {
        insert(treap[p].r, key);
        if (treap[treap[p].r].val > treap[p].val) zag(p);
    }
    push_up(p);
}

void remove(int &p, int key) {
    if (!p) return;
    if (treap[p].key == key) {
        if (treap[p].cnt > 1) {
            treap[p].cnt--;
        } else if (treap[p].l || treap[p].r) {
            if (!treap[p].r || treap[treap[p].l].val > treap[treap[p].r].val) {
                zig(p);
                remove(treap[p].r, key);
            } else {
                zag(p);
                remove(treap[p].l, key);
            }
        } else {
            p = 0;
        }
    } else if {
        (treap[p].key > key) remove(treap[p].l, key);
    } else {
        remove(treap[p].r, key);
    }
    push_up(p);
}

int get_rank_by_key(int p, int key) {
    // 通过数值找排名 //
    if (!p) return 0;
    if (treap[p].key == key) return treap[treap[p].l].size;
    if (treap[p].key > key) return get_rank_by_key(treap[p].l, key);
    return treap[treap[p].l].size + treap[p].cnt + get_rank_by_key(treap[p].r, key);
}

int get_key_by_rank(int p, int rank) {
    // 通过排名找数值 //
    if (!p) return inf;
    if (treap[treap[p].l].size >= rank) return get_key_by_rank(treap[p].l, rank);
    if (treap[treap[p].l].size + treap[p].cnt >= rank) return treap[p].key;
    return get_key_by_rank(treap[p].r, rank - treap[treap[p].l].size - treap[p].cnt);
}

int get_prev(int p, int key) {
    // 找前驱 //
    if (!p) return -inf;
    if (treap[p].key >= key) return get_prev(treap[p].l, key);
    return max(treap[p].key, get_prev(treap[p].r, key));
}

int get_next(int p, int key) {
    // 找后继 //
    if (!p) return inf;
    if (treap[p].key <= key) return get_next(treap[p].r, key);
    return min(treap[p].key, get_next(treap[p].l, key));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    build();
    rep(i, 1, n) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            insert(root, x);
        } else if (op == 2) {
            remove(root, x);
        } else if (op == 3) {
            cout << get_rank_by_key(root, x) << endl;
        } else if (op == 4) {
            cout << get_key_by_rank(root, x + 1) << endl;
        } else if (op == 5) {
            cout << get_prev(root, x) << endl;
        } else {
            cout << get_next(root, x) << endl;
        }
    }
    return 0;
}
```

## 无旋Treap

与旋转 Treap 同一个题目

```cpp
// created on Laptop of Lucian Xu

struct node {
    node *ch[2];
    int key, val;
    int cnt, size;

    node(int _key) : key(_key), cnt(1), size(1) {
        ch[0] = ch[1] = nullptr;
        val = rand();
    }

    // node(node *_node) {
    // key = _node->key, val = _node->val, cnt = _node->cnt, size = _node->size;
    // }

    inline void push_up() {
        size = cnt;
        if (ch[0] != nullptr) size += ch[0]->size;
        if (ch[1] != nullptr) size += ch[1]->size;
    }
};

struct treap {
#define _2 second.first
#define _3 second.second

    node *root;

    pair<node *, node *> split(node *p, int key) {
        if (p == nullptr) return {nullptr, nullptr};
        if (p->key <= key) {
            auto temp = split(p->ch[1], key);
            p->ch[1] = temp.first;
            p->push_up();
            return {p, temp.second};
        } else {
            auto temp = split(p->ch[0], key);
            p->ch[0] = temp.second;
            p->push_up();
            return {temp.first, p};
        }
    }

    pair<node *, pair<node *, node *> > split_by_rank(node *p, int rank) {
        if (p == nullptr) return {nullptr, {nullptr, nullptr}};
        int ls_size = p->ch[0] == nullptr ? 0 : p->ch[0]->size;
        if (rank <= ls_size) {
            auto temp = split_by_rank(p->ch[0], rank);
            p->ch[0] = temp._3;
            p->push_up();
            return {temp.first, {temp._2, p}};
        } else if (rank <= ls_size + p->cnt) {
            node *lt = p->ch[0];
            node *rt = p->ch[1];
            p->ch[0] = p->ch[1] = nullptr;
            return {lt, {p, rt}};
        } else {
            auto temp = split_by_rank(p->ch[1], rank - ls_size - p->cnt);
            p->ch[1] = temp.first;
            p->push_up();
            return {p, {temp._2, temp._3}};
        }
    }

    node *merge(node *u, node *v) {
        if (u == nullptr && v == nullptr) return nullptr;
        if (u != nullptr && v == nullptr) return u;
        if (v != nullptr && u == nullptr) return v;
        if (u->val < v->val) {
            u->ch[1] = merge(u->ch[1], v);
            u->push_up();
            return u;
        } else {
            v->ch[0] = merge(u, v->ch[0]);
            v->push_up();
            return v;
        }
    }

    void insert(int key) {
        auto temp = split(root, key);
        auto l_tr = split(temp.first, key - 1);
        node *new_node;
        if (l_tr.second == nullptr) {
            new_node = new node(key);
        } else {
            l_tr.second->cnt++;
            l_tr.second->push_up();
        }
        node *l_tr_combined = merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
    }

    void remove(int key) {
        auto temp = split(root, key);
        auto l_tr = split(temp.first, key - 1);
        if (l_tr.second->cnt > 1) {
            l_tr.second->cnt--;
            l_tr.second->push_up();
            l_tr.first = merge(l_tr.first, l_tr.second);
        } else {
            if (temp.first == l_tr.second) temp.first = nullptr;
            delete l_tr.second;
            l_tr.second = nullptr;
        }
        root = merge(l_tr.first, temp.second);
    }

    int get_rank_by_key(node *p, int key) {
        auto temp = split(p, key - 1);
        int ret = (temp.first == nullptr ? 0 : temp.first->size) + 1;
        root = merge(temp.first, temp.second);
        return ret;
    }

    int get_key_by_rank(node *p, int rank) {
        auto temp = split_by_rank(p, rank);
        int ret = temp._2->key;
        root = merge(temp.first, merge(temp._2, temp._3));
        return ret;
    }

    int get_prev(int key) {
        auto temp = split(root, key - 1);
        int ret = get_key_by_rank(temp.first, temp.first->size);
        root = merge(temp.first, temp.second);
        return ret;
    }

    int get_nex(int key) {
        auto temp = split(root, key);
        int ret = get_key_by_rank(temp.second, 1);
        root = merge(temp.first, temp.second);
        return ret;
    }
};

treap tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            tr.insert(x);
        } else if (op == 2) {
            tr.remove(x);
        } else if (op == 3) {
            cout << tr.get_rank_by_key(tr.root, x) << endl;
        } else if (op == 4) {
            cout << tr.get_key_by_rank(tr.root, x) << endl;
        } else if (op == 5) {
            cout << tr.get_prev(x) << endl;
        } else {
            cout << tr.get_nex(x) << endl;
        }
    }
    return 0;
}
```

## 用 01 Trie 实现的一种方式

同样的题目，注意使用 01 Trie 只能存在非负数。

速度能快不少，但只能单点操作，而且有点费空间。

```cpp
// 洛谷 P3369 【模板】普通平衡树

struct Treap {
    int id = 1, maxlog = 25;
    int ch[N * 25][2], siz[N * 25];

    int newnode() {
        id++;
        ch[id][0] = ch[id][1] = siz[id] = 0;
        return id;
    }

    void merge(int key, int cnt) {
        int u = 1;
        for (int i = maxlog - 1; i >= 0; i--) {
            int v = (key >> i) & 1;
            if (!ch[u][v]) ch[u][v] = newnode();
            u = ch[u][v];
            siz[u] += cnt;
        }
    }

    int get_key_by_rank(int rank) {
        int u = 1, key = 0;
        for (int i = maxlog - 1; i >= 0; i--) {
            if (siz[ch[u][0]] >= rank) {
                u = ch[u][0];
            } else {
                key |= (1 << i);
                rank -= siz[ch[u][0]];
                u = ch[u][1];
            }
        }
        return key;
    }

    int get_rank_by_key(int rank) {
        int key = 0;
        int u = 1;
        for (int i = maxlog - 1; i >= 0; i--) {
            if ((rank >> i) & 1) {
                key += siz[ch[u][0]];
                u = ch[u][1];
            } else {
                u = ch[u][0];
            }
            if (!u) break;
        }
        return key;
    }

    int get_prev(int x) { return get_key_by_rank(get_rank_by_key(x)); }
    int get_next(int x) { return get_key_by_rank(get_rank_by_key(x + 1) + 1); }
} treap;

const int num = 1e7;
int n, op, x;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> op >> x;
        if (op == 1) {
            treap.merge(x + num, 1);
        } else if (op == 2) {
            treap.merge(x + num, -1);
        } else if (op == 3) {
            std::cout << treap.get_rank_by_key(x + num) + 1 << endl;
        } else if (op == 4) {
            std::cout << treap.get_key_by_rank(x) - num << endl;
        } else if (op == 5) {
            std::cout << treap.get_prev(x + num) - num << endl;
        } else if (op == 6) {
            std::cout << treap.get_next(x + num) - num << endl;
        }
    }
    return 0;
}
```

