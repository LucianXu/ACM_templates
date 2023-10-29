# 最小费用最大流

在网络中获得最大流的同时要求费用最小。

## 没有负环的网络

### Dinic + SPFA

```CPP
struct edge {
    int from, to;
    LL cap, cost;

    edge(int u, int v, LL c, LL w) : from(u), to(v), cap(c), cost(w) {}
};

struct MCMF {
    int n, m = 0, s, t;
    std::vector<edge> e;
    vi g[N];
    int cur[N], vis[N];
    LL dist[N], minc;

    void init(int n) {
        for (int i = 0; i < n; i++) g[i].clear();
        e.clear();
        minc = m = 0;
    }

    void add(int from, int to, LL cap, LL cost) {
        e.push_back(edge(from, to, cap, cost));
        e.push_back(edge(to, from, 0, -cost));
        g[from].push_back(m++);
        g[to].push_back(m++);
    }

    bool spfa() {
        rep(i, 1, n) { dist[i] = INF, cur[i] = 0; }
        std::queue<int> q;
        q.push(s), dist[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int j = cur[u]; j < g[u].size(); j++) {
                edge& ee = e[g[u][j]];
                int v = ee.to;
                if (ee.cap && dist[v] > dist[u] + ee.cost) {
                    dist[v] = dist[u] + ee.cost;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = 1;
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    LL dfs(int u, LL now) {
        if (u == t) return now;
        vis[u] = 1;
        LL ans = 0;
        for (int& i = cur[u]; i < g[u].size() && ans < now; i++) {
            edge &ee = e[g[u][i]], &er = e[g[u][i] ^ 1];
            int v = ee.to;
            if (!vis[v] && ee.cap && dist[v] == dist[u] + ee.cost) {
                LL f = dfs(v, std::min(ee.cap, now - ans));
                if (f) {
                    minc += f * ee.cost, ans += f;
                    ee.cap -= f;
                    er.cap += f;
                }
            }
        }
        vis[u] = 0;
        return ans;
    }

    PLL mcmf() {
        LL maxf = 0;
        while (spfa()) {
            LL tmp;
            while ((tmp = dfs(s, INF))) maxf += tmp;
        }
        return std::makepair(maxf, minc);
    }
} minc_maxf;
```

### Primal-Dual 原始对偶算法

```cpp
struct edge {
    int from, to;
    LL cap, cost;

    edge(int u, int v, LL c, LL w) : from(u), to(v), cap(c), cost(w) {}
};

struct node {
    int v, e;

    node(int _v = 0, int _e = 0) : v(_v), e(_e) {}
};

const int maxn = 5000 + 10;

struct MCMF {
    int n, m = 0, s, t;
    std::vector<edge> e;
    vi g[maxn];
    int dis[maxn], vis[maxn], h[maxn];
    node p[maxn * 2];

    void add(int from, int to, LL cap, LL cost) {
        e.push_back(edge(from, to, cap, cost));
        e.push_back(edge(to, from, 0, -cost));
        g[from].push_back(m++);
        g[to].push_back(m++);
    }

    bool dijkstra() {
        std::priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
        for (int i = 1; i <= n; i++) {
            dis[i] = inf;
            vis[i] = 0;
        }
        dis[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            int u = q.top().ss;
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto i : g[u]) {
                edge ee = e[i];
                int v = ee.to, nc = ee.cost + h[u] - h[v];
                if (ee.cap and dis[v] > dis[u] + nc) {
                    dis[v] = dis[u] + nc;
                    p[v] = node(u, i);
                    if (!vis[v]) q.push({dis[v], v});
                }
            }
        }
        return dis[t] != inf;
    }

    void spfa() {
        std::queue<int> q;
        for (int i = 1; i <= n; i++) h[i] = inf;
        h[s] = 0, vis[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (auto i : g[u]) {
                edge ee = e[i];
                int v = ee.to;
                if (ee.cap and h[v] > h[u] + ee.cost) {
                    h[v] = h[u] + ee.cost;
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }

    PLL mcmf() {
        LL maxf = 0, minc = 0;
        spfa();
        while (dijkstra()) {
            LL minf = INF;
            for (int i = 1; i <= n; i++) h[i] += dis[i];
            for (int i = t; i != s; i = p[i].v) minf = std::min(minf, e[p[i].e].cap);
            for (int i = t; i != s; i = p[i].v) {
                e[p[i].e].cap -= minf;
                e[p[i].e ^ 1].cap += minf;
            }
            maxf += minf;
            minc += minf * h[t];
        }
        return std::make_pair(maxf, minc);
    }
} minc_maxf;
```



## 存在负环的网络