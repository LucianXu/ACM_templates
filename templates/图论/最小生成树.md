# 最小生成树

## 最小生成树

### Kruskal算法

```c++
std::vector<std::tuple<int, int, int>> edge;

// DSU //

auto kruskal = [&]() -> int {
    std::sort(all(edge), [&](std::tuple<int, int, int> a, std::tuple<int, int, int> b) {
        auto [x1, y1, w1] = a;
        auto [x2, y2, w2] = b;
        return w1 < w2;
    });
    int res = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        auto [a, b, w] = edge[i];
        a = find(a), b = find(b);
        if (a != b) {
            fa[a] = b;
            res += w;
            // res = std::max(res, w);
            cnt++;
        }
    }
    if (cnt < n - 1) return -1;
    return res;
}
```

### Prim算法

#### 朴素版

```c++
int n, m, ans;
int g[N][N], dist[N];
bool vis[N];
int prim(){
    memset(dist, 0x3f, sizeof dist);
    for(int i = 1; i < n - 1; i++){
        int t = -1;
        for(int j = 1; j <= n; j++){
            if(!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        }      
        if(i && dist[t] == INF) return 0x3f3f3f3f;
        if(i) ans += dist[t];
        // if(i) ans = max(ans, dist[t]);
        vis[t] = true;
        for(int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]);
    }
    return ans;
}

int main() {
    // 添边，g[i][j]的值和Floyd一样储存 //
    int t = prim();
    if(t == 0x3f3f3f3f) // 不连通 //
    else cout << t << endl;
}
```

就是朴素版Dijkstra算法。

#### 堆优化

```c++
typedef pair<int, int> PII;
int n, m, ans, cnt;
int h[M], e[M], ne[M], w[M], idx;
int dist[N];
bool vis[N];
void add(int a, int b, int c){
    e[++idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
}
void prim(){
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 1});
    while(!q.empty() && cnt < n){
        auto t = q.top();
        q.pop();
        int ver = t.second, distance = t.first;
        if(vis[ver]) continue;
        cnt++;
        ans += distance;
        // sum = max(sum, distance);
        vis[ver] = true;
        for(int i = h[ver]; i; i = ne[i]){
            int j = e[i];
            if(dist[j] > w[i]){
                dist[j] = w[i];
                q.push({dist[j], j});
            }
        }
    }
}

int main(){
    // 添边 //
    prim();
    if(cnt == n) cout << ans << endl;
    else // 不连通 //
}
```

就是堆优化版Dijkstra算法。

# UPDATE

## 2022.11.17

将 Kruskal 中的比较函数重载。