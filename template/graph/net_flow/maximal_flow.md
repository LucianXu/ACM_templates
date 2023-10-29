# 网络流

## Dinic 算法

### 理论

通过 BFS 将网络根据点到原点的距离（每条边长度定义为 $1$ ）分层，然后通过 DFS 暴力地在有效的网络中寻找增广路，不断循环上述步骤直至图中不存在增广路。

BFS 逻辑：

$u \to v$ 的条件满足下面两条：

1. $v$ 未必走过；

2. $e: u \to v$ 上还有残余流量，即当前 $e$ 的流量未达到其上限。

DFS 逻辑：

维护两个值：$u$：当前搜索到哪个点；$now$：可以增加的流量。$u \to v$ 的条件：

1. 在上一次 BFS 时，$v$ 在 $u$ 下面一层，即 $d[v] = d[u] + 1$。

2. 递归 $\operatorname{dfs}(v, now)$，这时可增加的流量上限要与 $e: u \to v$ 中可增加的流量上限取最小值，递归结果大于零才意味着可以增加流量。

优化：

1. 一次可以处理多条增广路。

2. 每一条有向边事实上只会增加一次流量，引入 $cur[N]$ 记录处理到了每个点的哪一条边以加快 DFS。

### 模板

```cpp
struct edge {
    int from, to;
    LL cap, flow;

    edge(int u, int v, LL c, LL f) : from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
    int n, m = 0, s, t;
    std::vector<edge> e;
    vi g[N];
    int d[N], cur[N], vis[N];

    void init(int n) {
        for (int i = 0; i < n; i++) g[i].clear();
        e.clear();
        m = 0;
    }

    void add(int from, int to, LL cap) {
        e.push_back(edge(from, to, cap, 0));
        e.push_back(edge(to, from, 0, 0));
        g[from].push_back(m++);
        g[to].push_back(m++);
    }

    bool bfs() {
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
        }
        std::queue<int> q;
        q.push(s), d[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); i++) {
                edge& ee = e[g[u][i]];
                if (!vis[ee.to] and ee.cap > ee.flow) {
                    vis[ee.to] = 1;
                    d[ee.to] = d[u] + 1;
                    q.push(ee.to);
                }
            }
        }
        return vis[t];
    }

    LL dfs(int u, LL now) {
        if (u == t || now == 0) return now;
        LL flow = 0, f;
        for (int& i = cur[u]; i < g[u].size(); i++) {
            edge& ee = e[g[u][i]];
            edge& er = e[g[u][i] ^ 1];
            if (d[u] + 1 == d[ee.to] and (f = dfs(ee.to, std::min(now, ee.cap - ee.flow))) > 0) {
                ee.flow += f, er.flow -= f;
                flow += f, now -= f;
                if (now == 0) break;
            }
        }
        return flow;
    }

    LL dinic() {
        LL ans = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++) cur[i] = 0;
            ans += dfs(s, INF);
        }
        return ans;
    }
} maxf;
```

## HLPP 算法

抄板子吧，别管原理了。

留一个图吧。

![1152](https://oi-wiki.org/graph/flow/images/1152.png)

```cpp
// P4722 【模板】最大流 加强版 / 预流推进 //

struct HLPP {
    int n, m = 0, s, t;
    std::vector<edge> e;      // 边 //
    std::vector<node> nd;     // 点 //
    std::vector<int> g[N];    // 点的连边编号 //
    std::priority_queue<node> q;
    std::queue<int> qq;
    bool vis[N];
    int cnt[N];

    void init() {
        e.clear();
        nd.clear();
        for (int i = 0; i <= n + 1; i++) {
            nd.pushback(node(inf, i, 0));
            g[i].clear();
            vis[i] = false;
        }
    }

    void add(int u, int v, LL w) {
        e.pushback(edge(u, v, w));
        e.pushback(edge(v, u, 0));
        g[u].pushback(m++);
        g[v].pushback(m++);
    }

    void bfs() {
        nd[t].hight = 0;
        qq.push(t);
        while (!qq.empty()) {
            int u = qq.front();
            qq.pop();
            vis[u] = false;
            for (auto j : g[u]) {
                int v = e[j].to;
                if (e[j].cap == 0 && nd[v].hight > nd[u].hight + 1) {
                    nd[v].hight = nd[u].hight + 1;
                    if (vis[v] == false) {
                        qq.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return;
    }

    void _push(int u) {
        for (auto j : g[u]) {
            edge &ee = e[j], &er = e[j ^ 1];
            int v = ee.to;
            node &nu = nd[u], &nv = nd[v];
            if (ee.cap && nv.hight + 1 == nu.hight) {
                // 推流 //
                LL flow = std::min(ee.cap, nu.flow);
                ee.cap -= flow, er.cap += flow;
                nu.flow -= flow, nv.flow += flow;
                if (vis[v] == false && v != t && v != s) {
                    q.push(nv);
                    vis[v] = true;
                }
                if (nu.flow == 0) break;
            }
        }
    }

    void relabel(int u) {
        nd[u].hight = inf;
        for (auto j : g[u]) {
            int v = e[j].to;
            if (e[j].cap && nd[v].hight + 1 < nd[u].hight) {
                nd[u].hight = nd[v].hight + 1;
            }
        }
    }

    LL hlpp() {
        bfs();
        if (nd[s].hight == inf) return 0;
        nd[s].hight = n;
        for (int i = 1; i <= n; i++) {
            if (nd[i].hight < inf) cnt[nd[i].hight]++;
        }
        for (auto j : g[s]) {
            int v = e[j].to;
            int flow = e[j].cap;
            if (flow) {
                e[j].cap -= flow, e[j ^ 1].cap += flow;
                nd[s].flow -= flow, nd[v].flow += flow;
                if (vis[v] == false && v != s && v != t) {
                    q.push(nd[v]);
                    vis[v] = true;
                }
            }
        }
        while (!q.empty()) {
            int u = q.top().id;
            q.pop();
            vis[u] = false;
            _push(u);
            if (nd[u].flow) {
                cnt[nd[u].hight]--;
                if (cnt[nd[u].hight] == 0) {
                    for (int i = 1; i <= n; i++) {
                        if (i != s && i != t && nd[i].hight > nd[u].hight && nd[i].hight < n + 1) {
                            nd[i].hight = n + 1;
                        }
                    }
                }
                // 上面为 gap 优化 //
                relabel(u);
                cnt[nd[u].hight]++;
                q.push(nd[u]);
                vis[u] = true;
            }
        }
        return nd[t].flow;
    }
} maxf;
```