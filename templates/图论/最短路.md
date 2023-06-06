# 最短路

## 最短路

### Floyd算法

```c++
auto floyd = [&]() -> vvi {
    vvi dist(n + 1, vi(n + 1, inf));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            Min(dist[i][j], e[i][j]);
        }
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                Min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
};
```

### Dijkstra算法

#### 堆优化

```c++
auto dijkstra = [&](int s) -> vl {
    vl dist(n + 1, INF);
    vi vis(n + 1, 0);
    dist[s] = 0;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> q;
    q.emplace(0LL, s);
    while (!q.empty()) {
        auto [dis, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (const auto& [v, w] : e[u]) {
            if (dist[v] > dis + w) {
                dist[v] = dis + w;
                q.emplace(dist[v], v);
            }
        }
    }
    return dist;
};
```

### Bellman - fold算法

```c++
int n, m, s;
int dist[N];
struct node{
    int from, to, w;
}edge[M];
void bellman_fold(int s){
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    for(int i = 1; i <= n; i++){
        bool flag = true;
        for(int j = 1; j <= m; j++){
            int a = edge[j].from, b = edge[j].to, w = edge[j].w;
            if(dist[a] == 0x3f3f3f3f) continue;
            if(dist[b] > dist[a] + w){
                dist[b] = dist[a] + w;
                flag = false;
            }
        }
        if(flag) break;
    }
}
```

### SPFA算法

```c++
int n, m, s;
vl dist(n + 1, INF);
std::vector<bool> vis(n + 1);
std::vector<PLI > e(n + 1);
 
void spfa(int s){
    rep(i, 1, n) dist[i] = INF;
    dist[s] = 0;
    std::queue<int> q;
    q.push(s);
    vis[s] = true;
    while(q.size()){
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for(auto j : e[u]){
            int v = j.ff; LL w = j.ss;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                if(!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}
```

## Johnson

```cpp
// Johnson 全源最短路 //

// 负环 //
vl dist1(n + 1);
vi vis(n + 1), cnt(n + 1);
auto spfa = [&]() -> bool {
    std::queue<int> q;
    for (int u = 1; u <= n; u++) {
        q.push(u);
        vis[u] = false;
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (auto [v, w] : e[u]) {
            if (dist1[v] > dist1[u] + w) {
                dist1[v] = dist1[u] + w;
                Max(cnt[v], cnt[u] + 1);
                if (cnt[v] >= n) return true;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
};

// dijkstra //
vl dist2(n + 1);
auto dijkstra = [&](int s) {
    for (int u = 1; u <= n; u++) {
        dist2[u] = 1e9;
        vis[u] = false;
    }
    dist2[s] = 0;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> q;
    q.emplace(0, s);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (const auto& [v, w] : e[u]) {
            if (dist2[v] > d + w) {
                dist2[v] = d + w;
                q.emplace(dist2[v], v);
            }
        }
    }
};

if (spfa()) {
    std::cout << -1 << '\n';
    return;
}
for (int u = 1; u <= n; u++) {
    for (auto& [v, w] : e[u]) {
        w += dist1[u] - dist1[v];
    }
}
for (int u = 1; u <= n; u++) {
    dijkstra(u);
}
```

## 最短路计数

### Dijkstra

```c++
auto dijkstra = [&](int s) -> std::pair<vl, vi> {
    vl dist(n + 1, INF);
    vi cnt(n + 1), vis(n + 1);
    dist[s] = 0;
    cnt[s] = 1;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> q;
    q.emplace(0LL, s);
    while (!q.empty()) {
        auto [dis, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (const auto& [v, w] : e[u]) {
            if (dist[v] > dis + w) {
                dist[v] = dis + w;
                cnt[v] = cnt[u];
                q.push({dist[v], v});
            } else if (dist[v] == dis + w) {
                // cnt[v] += cnt[u];
                cnt[v] += cnt[u];
                cnt[v] %= 100003;
            }
        }
    }
    return {dist, cnt};
};
```

### Floyd

```c++
auto floyd() = [&] -> std::pair<vvi, vvi> {
    vvi dist(n + 1, vi(n + 1, inf));
    vvi cnt(n + 1, vi(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            Min(dist[i][j], e[i][j]);
        }
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] == dist[i][k] + dist[k][j]) {
                    cnt[i][j] += cnt[i][k] * cnt[k][j];
                } else if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    cnt[i][j] = cnt[i][k] * cnt[k][j];
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return {dist, cnt};
};
```

## 负环

### SPFA

判断的是最短路长度.

```c++
auto spfa = [&]() -> bool {
    std::queue<int> q;
    vi vis(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        q.push(i);
        vis[i] = true;
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (const auto& [v, w] : e[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
}
```



# 分层最短路

有一个 $n$ 个点 $m$ 条边的无向图，你可以选择 $k$ 条道路以零代价通行，求 $s$ 到 $t$ 的最小花费。

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, k, s, t;
    std::cin >> n >> m >> k;
    std::cin >> s >> t;
    std::vector<std::vector<PIL>> e(n * (k + 1) + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        e[a].emplace_back(b, c);
        e[b].emplace_back(a, c);
        for (int j = 1; j <= k; j++) {
            e[a + (j - 1) * n].emplace_back(b + j * n, 0);
            e[b + (j - 1) * n].emplace_back(a + j * n, 0);
            e[a + j * n].emplace_back(b + j * n, c);
            e[b + j * n].emplace_back(a + j * n, c);
        }
    }

    auto dijkstra = [&](int s) -> vl {};

    vl dist = dijkstra(s);
    LL ans = INF;
    for (int i = t; i <= n * (k + 1); i += n) {
        Min(ans, dist[i]);
    }

    std::cout << ans << endl;

    return 0;
}
```

# UPDATE

## 2022.11.17

将常用的板子（堆优化 Dijkstra、SPFA 的最短路以及最短路计数）中的链式前向星该换 vector；将 SPFA 判负环的错误改正。