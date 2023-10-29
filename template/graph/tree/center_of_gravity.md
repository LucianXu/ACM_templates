# 树的重心

```cpp
int sum;    /* 点权和 */
vi size(n + 1), weight(n + 1), w(n + 1), depth(n + 1);
std::array<int, 2> centroid = {0, 0};
auto get_centroid = [&](auto&& self, int u, int fa) -> void {
    size[u] = w[u];
    weight[u] = 0;
    for (auto v : e[u]) {
        if (v == fa) continue;
        self(self, v, u);
        size[u] += size[v];
        Max(weight[u], size[v]);
    }
    Max(weight[u], sum - size[u]);
    if (weight[u] <= sum / 2) {
        centroid[centroid[0] != 0] = u;
    }
};
```
