# 树的直径

## 两次DFS

```c++
vvi e(n + 1);
vi d(n + 1);
int ans, id;
void dfs(int u, int fa){
    for(auto v : e[u]){
        if(v == fa) continue;
          d[v] = d[u] + 1;
          if(d[v] > d[id]) id = i;
          dfs(v, u);
    }
}
int main(){
    dfs(1, 0);
    d[id] = 0;
    dfs(id, 0);
    cout << d[id] << endl;
    return 0;
}
```

## 树形DP

```c++
vvi e(n + 1);
vi d1(n + 1), d2(n + 1);
int ans;
void dfs(int u, int fa){
    d1[u] = d2[u] = 0;
    for(int v : e[u]){
        if(v == fa) continue;
        dfs(v, u);
        int t = d1[v] + 1;
        if(t > d1[u]){
            d2[u] = d1[u];
            d1[u] = t;
        }
        else if(t > d2[u]){
            d2[u] = t;
        }
    }
    Max(ans, d1[u] + d2[u]);
}
int main(){
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}

```

## 特殊的一些东西

如果要找到直径上的的点，只能用两次DFS。

```c++
struct node{
    int to, w;
};
vector<node> v[N];
int ans, id, d[N], f[N];
void add(int a, int b, int w){
    node tmp;
    tmp.to = b;
    tmp.w = w;
    v[a].push_back(tmp);
}
void dfs(int u, int fa){
    f[u] = fa;
    for(auto i : v[u]){
        if(i.to != fa){
            d[i.to] = d[u] + i.w;
            if(d[i.to] > d[id]){
                id = i.to;
            }
            dfs(i.to, u);
        }
    }
}
// 得到直径上的点 //
for(int i = id; i != 0; i = f[i]){
    cout << i << ' ';
}
```

上面的代码都是边权为1的。如果边权为负，只能用树形DP。

```c++
struct node{
    int to, w;
};
vector<node> v[N];
int ans, id, d1[N], d2[N];
void add(int a, int b, int w){
    node tmp;
    tmp.to = b;
    tmp.w = w;
    v[a].push_back(tmp);
}
void dfs(int u, int fa){
    d1[u] = d2[u] = 0;
    for(auto i : v[u]){
        if(i.to != fa){
            dfs(i.to, u);
            int t = d1[i.to] + i.w;
            if(t > d1[u]){
                d2[u] = d1[u];
                d1[u] = t;
            }
            else if(t > d2[u]){
                d2[u] = t;
            }
        }
    }
    ans = max(ans, d1[u] + d2[u]);
}
```

