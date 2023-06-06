# 强连通分量

## Tarjan算法

```c++
vi dfn(n + 1), low(n + 1), stk(n + 1), belong(n + 1);
int timestamp = 0, top = 0, scc_cnt = 0;
std::vector<bool> in_stk(n + 1);

auto tarjan = [&](auto&& self, int u) -> void {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    in_stk[u] = true;
    for (const auto& v : e[u]) {
        if (!dfn[v]) {
            self(self, v);
            Min(low[u], low[v]);
        } else if (in_stk[v]) {
            Min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk[top--];
            in_stk[v] = false;
            belong[v] = scc_cnt;
        } while (v != u);
    }
};
```

## Kora Saju算法

```c++
int n, m;
int belong[N], stk[N], tops, cc_cnt;
bool vis[N];
vector<int> g1[N], g2[N];
void add(int a, int b){
    g1[a].push_back(b);
    g2[b].push_back(a);
}
void dfs1(int u){
    vis[u] = true;
    for (int v : g1[u]){
        if (!vis[v]) dfs1(v);
    }
    stk[++top] = u;
}
void dfs2(int u){
    belong[u] = scc_cnt;
    for (int v : g2[u]){
        if (!belong[v]) dfs2(v);
    }
}
void kosaraju(){
    scc_cnt = 0;
    for (int i = 1; i <= n; i++){
        if (!vis[i]) dfs1(i);
    }
    for (int i = n; i >= 1; i--){
        if (!belong[stk[i]]){
            scc_cnt++;
            dfs2(stk[i]);
        }
    }
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    kosaraju();
    return 0;
}
```

## Garbow算法

```c++
int n, m;
int e[N], ne[N], h[N], idx;
int belong[N], stack1[N], stack2[N], low[N], timestamp, p1, p2, scc_cnt;
void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}
int garbow(int u){
    stack1[++p1] = u;
    stack2[++p2] = u;
    low[u] = ++timestamp;
    for (int i = h[u]; i != -1; i = ne[i]){
        int v = e[i];
        if (!low[v]){
            garbow(v);
        }
        else if (!belong[v]){
            while (low[stack2[p2]] > low[v]) p2--;
        }
    }
    if (stack2[p2] == u){
        p2--;
        scc_cnt++;
        do{
            belong[stack1[p1]] = scc_cnt;
        } while (stack1[p1--] != u);
    }
    return 0;
}
void init(){
    timestamp = scc_cnt = 0;
    p1 = p2 = 0;
    memset(belong, 0, sizeof(belong));
    memset(low, 0, sizeof(low));
}

int main(){
    cin >> n >> m;
    init();
    memset(h, -1, sizeof(h));
    for (int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    for (int i = 1; i <= n; i++){
        if (!low[i]) garbow(i);
    }
    return 0;
}
```

以上三种方法均使用 scc_cnt 计算强连通分量的个数，belong[ N ] 保存每个点在第几个强连通分量。

可以使用以下方法按 $1$ 至 $n$ 的顺序输出每个点所在的强连通分量包含哪些点

```c++
vi ans(n);

cout << scc_cnt;
for (int i = 1; i <= n; i++){
    ans[belong[i]].push_back(i);
}
for (int i = 1; i <= n; i++){
    int t = belong[i];
    if (!ans[t].empty()){
        cout << endl;
        sort(ans[t].begin(), ans[t].end());
        for (int j = 0; j < ans[t].size(); j++){
            cout << ans[t][j] << ' ';
        }
        while (!ans[t].empty()){
            ans[t].pop_back();
        }
    }
}
```

## 缩点

在读入边时就将起点和终点分别读入 from[ N ] 和 to[ N ] ，并且将已经存入的边删除。

边无权值，点有权值

```c++
void shrink_point(){
    memset(h, 0, sizeof(h));
    idx = 0;
    for(int i = 1; i <= n; i++){
        w_[belong[i]] += w[i];
    }
    for(int i = 1; i <= m; i++){
        if(belong[from[i]] != belong[to[i]]){
            add(belong[from[i]], belong[to[i]]);
        }
    }
}
```

边有权值，点无权值，将强连通分量的边权值总和作为缩点后的点权值

```c++
void shrink_point(){
    memset(h, 0, sizeof(h));
    idx = 0;
    for(int i = 1; i <= m; i++){
        if(belong[from[i]] != belong[to[i]]){
            add(belong[from[i]], belong[to[i]], -w[i]);
        }
        else{
            w_[belong[to[i]]] -= w[i];
        }
    }
}
```

