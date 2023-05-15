# 线段树套线段树

$n$ 个三维数对 $(a_i, b_i, c_i)$，设 $f(i)$ 表示 $a_j \leqslant a_i$ 且 $b_j \leqslant b_i$ 且  $c_j \leqslant c_i$ 且 $i \neq j$ 的个数。输出 $f(i) \ (0 \leqslant i \leqslant n - 1)$  的值。

```cpp
// 洛谷 P3810 【模板】三维偏序（陌上花开）

struct node1 {
    int l, r, root;
} tr1[N << 2];

struct node2 {
    int ch[2], cnt;
} tr2[N << 7];

struct node {
    int x, y, z, cnt;

    bool operator==(const node& a) { return (x == a.x && y == a.y && z == a.z); }

} data[N];

bool cmp(node a, node b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

int root_tot, n, m, ans[N], anss[N];

void build(int u, int l, int r) {
    tr1[u].l = l, tr1[u].r = r;
    if (l != r) {
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
}

void modify_2(int& u, int l, int r, int pos) {
    if (u == 0) u = ++root_tot;
    tr2[u].cnt++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        modify_2(tr2[u].ch[0], l, mid, pos);
    } else {
        modify_2(tr2[u].ch[1], mid + 1, r, pos);
    }
}

int query_2(int& u, int l, int r, int x, int y) {
    if (u == 0) return 0;
    if (x <= l && r <= y) return tr2[u].cnt;
    int mid = (l + r) >> 1, ans = 0;
    if (x <= mid) ans += query_2(tr2[u].ch[0], l, mid, x, y);
    if (mid < y) ans += query_2(tr2[u].ch[1], mid + 1, r, x, y);
    return ans;
}

void modify_1(int u, int l, int r, int t) {
    modify_2(tr1[u].root, 1, m, data[t].z);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (data[t].y <= mid) {
        modify_1(u << 1, l, mid, t);
    } else {
        modify_1(u << 1 | 1, mid + 1, r, t);
    }
}

int query_1(int u, int l, int r, int t) {
    if (1 <= l && r <= data[t].y) return query_2(tr1[u].root, 1, m, 1, data[t].z);
    int mid = (l + r) >> 1, ans = 0;
    if (1 <= mid) ans += query_1(u << 1, l, mid, t);
    if (mid < data[t].y) ans += query_1(u << 1 | 1, mid + 1, r, t);
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> n >> m;
    rep(i, 1, n) {
        int x, y, z;
        std::cin >> x >> y >> z;
        data[i] = {x, y, z};
    }
    std::sort(data + 1, data + n + 1, cmp);
    build(1, 1, m);
    rep(i, 1, n) {
        modify_1(1, 1, m, i);
        ans[i] = query_1(1, 1, m, i);
    }
    per(i, n - 1, 1) {
        if (data[i] == data[i + 1]) ans[i] = ans[i + 1];
    }
    rep(i, 1, n) anss[ans[i]]++;
    rep(i, 1, n) std::cout << anss[i] << endl;

    return 0;
}
```

# 线段树套平衡树

长度为 $n$ 的序列和 $m$ 此操作，包含 $5$ 种操作：

1. $l \ r \ k$：询问区间 $[l \sim r]$ 中数 $k$ 的排名。
2. $l \ r \ k$：询问区间 $[l \sim r]$ 中排名为 $k$ 的数。
3. $pos \ k$：将序列中 $pos$ 位置的数修改为 $k$ 。
4. $l \ r \ k$：询问区间 $[l \sim r]$ 中数 $k$ 的前驱。
5. $l \ r \ k$：询问区间 $[l \sim r]$ 中数 $k$ 的后继。

### Treap 实现

```cpp
// 洛谷 P3380 【模板】二逼平衡树（树套树）

int n, m, op, l, r, pos, key, root_tot;
int a[N];

struct node2 {
    node2 *ch[2];
    int key, val;
    int cnt, size;

    node2(int _key) : key(_key), cnt(1), size(1) {
        ch[0] = ch[1] = nullptr;
        val = rand();
    }

    // node2(node2 *_node2) {
    // key = _node2->key, val = _node2->val, cnt = _node2->cnt, size = _node2->size;
    // }

    inline void push_up() {
        size = cnt;
        if (ch[0] != nullptr) size += ch[0]->size;
        if (ch[1] != nullptr) size += ch[1]->size;
    }
};

struct treap {
    ···
};

treap tr2[N << 4];

struct node1 {
    int l, r, root;
} tr1[N << 4];

void build(int u, int l, int r) {
    tr1[u] = {l, r, u};
    root_tot = std::max(root_tot, u);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int pos, int key) {
    tr2[u].insert(key);
    if (tr1[u].l == tr1[u].r) return;
    int mid = (tr1[u].l + tr1[u].r) >> 1;
    if (pos <= mid){
        modify(u << 1, pos, key);
    }
    else{
        modify(u << 1 | 1, pos, key);
    }
}

int get_rank_by_key_in_interval(int u, int l, int r, int key) {
    if (l <= tr1[u].l && tr1[u].r <= r) return tr2[u].get_rank_by_key(tr2[u].root, key) - 2;
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = 0;
    if (l <= mid) ans += get_rank_by_key_in_interval(u << 1, l, r, key);
    if (mid < r) ans += get_rank_by_key_in_interval(u << 1 | 1, l, r, key);
    return ans;
}

int get_key_by_rank_in_interval(int u, int l, int r, int rank) {
    int L = 0, R = 1e8;
    while (L < R) {
        int mid = (L + R + 1) / 2;
        if (get_rank_by_key_in_interval(1, l, r, mid) < rank){
            L = mid;
        }
        else{
            R = mid - 1;
        }
    }
    return L;
}

void change(int u, int pos, int pre_key, int key) {
    tr2[u].remove(pre_key);
    tr2[u].insert(key);
    if (tr1[u].l == tr1[u].r) return;
    int mid = (tr1[u].l + tr1[u].r) >> 1;
    if (pos <= mid){
        change(u << 1, pos, pre_key, key);
    }
    else{
        change(u << 1 | 1, pos, pre_key, key);
    }
}

int get_prev_in_interval(int u, int l, int r, int key) {
    if (l <= tr1[u].l && tr1[u].r <= r) return tr2[u].get_prev(key);
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = -inf;
    if (l <= mid) ans = std::max(ans, get_prev_in_interval(u << 1, l, r, key));
    if (mid < r) ans = std::max(ans, get_prev_in_interval(u << 1 | 1, l, r, key));
    return ans;
}

int get_nex_in_interval(int u, int l, int r, int key) {
    if (l <= tr1[u].l && tr1[u].r <= r) return tr2[u].get_nex(key);
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = inf;
    if (l <= mid) ans = std::min(ans, get_nex_in_interval(u << 1, l, r, key));
    if (mid < r) ans = std::min(ans, get_nex_in_interval(u << 1 | 1, l, r, key));
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    srand(time(0));

    std::cin >> n >> m;
    build(1, 1, n);
    rep(i, 1, n) {
        std::cin >> a[i];
        modify(1, i, a[i]);
    }
    rep(i, 1, root_tot) { tr2[i].insert(inf), tr2[i].insert(-inf); }
    rep(i, 1, m) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> l >> r >> key;
            std::cout << get_rank_by_key_in_interval(1, l, r, key) + 1 << endl;
        } else if (op == 2) {
            std::cin >> l >> r >> key;
            std::cout << get_key_by_rank_in_interval(1, l, r, key) << endl;
        } else if (op == 3) {
            std::cin >> pos >> key;
            change(1, pos, a[pos], key);
            a[pos] = key;
        } else if (op == 4) {
            std::cin >> l >> r >> key;
            std::cout << get_prev_in_interval(1, l, r, key) << endl;
        } else if (op == 5) {
            std::cin >> l >> r >> key;
            std::cout << get_nex_in_interval(1, l, r, key) << endl;
        
    }

    return 0;
}
```

然而洛谷上的会 T 两个点，Loj 和 ACwing 上的能过。



### Splay 实现

```cpp
// 洛谷 P3380 【模板】二逼平衡树（树套树）

int n, m, op, l, r, pos, key, root_tot;
int a[N];

struct node{
    int ch[2], fa, key, siz, cnt;
    
    void init(int _fa, int _key){
        fa = _fa, key = _key, siz = cnt = 1;
    }
    
    void clear(){
        ch[0] = ch[1] = fa = key = siz = cnt = 0;
    }
}tr[N * 30];

struct splay{
    
    int idx;
    
    bool get(int u){
        return u == tr[tr[u].fa].ch[1];
    }
    
    void pushup(int u){
        tr[u].siz = tr[tr[u].ch[0]].siz + tr[tr[u].ch[1]].siz + tr[u].cnt;
    }
    
    void rotate(int x){
        int y = tr[x].fa, z = tr[y].fa;
        int op = get(x);
        tr[y].ch[op] = tr[x].ch[op ^ 1];
        if(tr[x].ch[op ^ 1]) tr[tr[x].ch[op ^ 1]].fa = y;
        tr[x].ch[op ^ 1] = y;
        tr[y].fa = x, tr[x].fa = z;
        if(z) tr[z].ch[y == tr[z].ch[1]] = x;
        pushup(y), pushup(x);
    }
    
    void opt(int& root, int u, int k){
        for(int f = tr[u].fa; f = tr[u].fa, f != k; rotate(u)){
            if(tr[f].fa != k) rotate(get(u) == get(f) ? f : u);
        }
        if(k == 0) root = u;
    }
    
    void insert(int& root, int key){
        if(tr[root].siz == 0){
            idx++;
            tr[idx].init(0, key);
            root = idx;
            return;
        }
        int u = root, f = 0;
        while(1){
            if(tr[u].key == key){
                tr[u].cnt++;
                pushup(u), pushup(f);
                opt(root, u, 0);
                break;
            }
            f = u, u = tr[u].ch[tr[u].key < key];
            if(!u){
                idx++;
                tr[idx].init(f, key);
                tr[f].ch[tr[f].key < key] = idx;
                pushup(idx), pushup(f);
                opt(root, idx, 0);
                break;
            }
        }
    }
    
    int kth(int& root, int rank){
        int u = root;
        while(1){
            if(tr[u].ch[0] && rank <= tr[tr[u].ch[0]].siz) u = tr[u].ch[0];
            else{
                rank -= tr[tr[u].ch[0]].siz + tr[u].cnt;
                if(rank <= 0){
                    opt(root, u, 0);
                    return u;
                }
                else u = tr[u].ch[1];
            }
        }
    }
    
    int nlt(int& root, int key){
        int rank = 0, u = root;
        while(1){
            if(tr[u].key > key) u = tr[u].ch[0];
            else{
                rank += tr[tr[u].ch[0]].siz;
                if(tr[u].key == key){
                    opt(root, u, 0);
                    return rank + 1;
                }
                rank += tr[u].cnt;
                if(tr[u].ch[1]) u = tr[u].ch[1];
                else return rank + 1;
            }
        }
    }
    
    int get_prev(int& root, int key){
        return kth(root, nlt(root, key) - 1);
    }
    
    int get_next(int& root, int key){
        return kth(root, nlt(root, key + 1));
    }
    
    void remove(int& root, int key){
        nlt(root, key);
        if(tr[root].cnt > 1){
            tr[root].cnt--;
            pushup(root);
            return;
        }
        int u = root, l = get_prev(root, key);
        tr[tr[u].ch[1]].fa = l;
        tr[l].ch[1] = tr[u].ch[1];
        tr[u].clear();
        pushup(root);
    }
    
    void output(int u){
        if(tr[u].ch[0]) output(tr[u].ch[0]);
        std::cout << tr[u].key << ' ';
        if(tr[u].ch[1]) output(tr[u].ch[1]);
    }
    
}splay;

struct node1{
    int l, r, root;
}tr1[N * 4];

void build(int u, int l, int r){
    tr1[u] = {l, r, u};
    root_tot = splay.idx = std::max(root_tot, u);
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int pos, int key){
    splay.insert(tr1[u].root, key);
    if(tr1[u].l == tr1[u].r) return;
    int mid = (tr1[u].l + tr1[u].r) >> 1;
    if(pos <= mid) modify(u << 1, pos, key);
    else modify(u << 1 | 1, pos, key);
}

int get_rank_by_key_in_interval(int u, int l, int r, int key){
    if(l <= tr1[u].l && tr1[u].r <= r) 
        return splay.nlt(tr1[u].root, key) - 2;
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = 0;
    if(l <= mid) ans += get_rank_by_key_in_interval(u << 1, l, r, key);
    if(mid < r) ans += get_rank_by_key_in_interval(u << 1 | 1, l, r, key);
    return ans;
}

int get_key_by_rank_in_interval(int u, int l, int r, int rank){
    int L = 0, R = 1e8;
    while(L < R){
        int mid = (L + R + 1) / 2;
        if(get_rank_by_key_in_interval(1, l, r, mid) < rank) L = mid;
        else R = mid - 1;
    }
    return L;
}

void change(int u, int pos, int pre_key, int key){
    splay.remove(tr1[u].root, pre_key);
    splay.insert(tr1[u].root, key);
    if(tr1[u].l == tr1[u].r) return;
    int mid = (tr1[u].l + tr1[u].r) >> 1;
    if(pos <= mid) change(u << 1, pos, pre_key, key);
    else change(u << 1 | 1, pos, pre_key, key);
}

int get_prev_in_interval(int u, int l, int r, int key){
    if(l <= tr1[u].l && tr1[u].r <= r)
        return tr[splay.get_prev(tr1[u].root, key)].key;
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = -inf;
    if(l <= mid) ans = std::max(ans, get_prev_in_interval(u << 1, l, r, key));
    if(mid < r) ans = std::max(ans, get_prev_in_interval(u << 1 | 1, l, r, key));
    return ans;
        
}

int get_next_in_interval(int u, int l, int r, int key){
    if(l <= tr1[u].l && tr1[u].r <= r)
        return tr[splay.get_next(tr1[u].root, key)].key;
    int mid = (tr1[u].l + tr1[u].r) >> 1, ans = inf;
    if(l <= mid) ans = std::min(ans, get_next_in_interval(u << 1, l, r, key));
    if(mid < r) ans = std::min(ans, get_next_in_interval(u << 1 | 1, l, r, key));
    return ans;
}

int main(){
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    srand(time(0));
    
    std::cin >> n >> m;
    build(1, 1, n);
    rep(i, 1, n){
        std::cin >> a[i];
        modify(1, i, a[i]);
    }
    rep(i, 1, root_tot){
        splay.insert(tr1[i].root, inf), splay.insert(tr1[i].root, -inf); 
    }
    rep(i, 1, m){
        std::cin >> op;
        if(op == 1){
            std::cin >> l >> r >> key;
            std::cout << get_rank_by_key_in_interval(1, l, r, key) + 1 << endl;
        }
        else if(op == 2){
            std::cin >> l >> r >> key;
            std::cout << get_key_by_rank_in_interval(1, l, r, key) << endl;
        }
        else if(op == 3){
            std::cin >> pos >> key;
            change(1, pos, a[pos], key);
            a[pos] = key;
        }
        else if(op == 4){
            std::cin >> l >> r >> key;
            std::cout << get_prev_in_interval(1, l, r, key) << endl;
        }
        else if(op == 5){
            std::cin >> l >> r >> key;
            std::cout << get_next_in_interval(1, l, r, key) << endl;
        }
    }
    
    return 0;
}
```

然而洛谷吸氧能过，ACwing能过，Loj T一堆。