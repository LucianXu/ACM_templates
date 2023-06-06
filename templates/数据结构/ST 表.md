# ST 表

用于解决可重复问题的数据结构。

可重复问题是指对运算 $opt$，满足 $x \ opt \ x = x$。

## 一维 ST 表

```cpp
// ST //
vvi f(n + 1, vi(30));
vi Log2(n + 1);
auto ST_init = [&]() -> void {
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
        if (i > 1) Log2[i] = Log2[i / 2] + 1;
    };
    int t = Log2[n];
    for (int j = 1; j <= t; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
};

auto ST_query = [&](int l, int r) -> int {
    int t = Log2[r - l + 1];
    return std::max(f[l][t], f[r - (1 << t) + 1][t]);
};
```

## 二维 ST 表

```cpp
// ST //
std::vector f(n + 1, std::vector<std::array<std::array<int, 30>, 30>>(m + 1));
vi Log2(n + 1);
auto ST_init = [&]() -> void {
    for (int i = 2; i <= std::max(n, m); i++) {
        Log2[i] = Log2[i / 2] + 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            f[i][j][0][0] = a[i][j];
        }
    }
    for (int ki = 0; ki <= Log2[n]; ki++) {
        for (int kj = 0; kj <= Log2[n]; kj++) {
            if (!ki && !kj) continue;
            for (int i = 1; i <= n - (1 << ki) + 1; i++) {
                for (int j = 1; j <= m - (1 << kj) + 1; j++) {
                    if (ki) {
                        f[i][j][ki][kj] =
                            std::max(f[i][j][ki - 1][kj], f[i + (1 << (ki - 1))][j][ki - 1][kj]);
                    } else {
                        f[i][j][ki][kj] =
                            std::max(f[i][j][ki][kj - 1], f[i][j + (1 << (kj - 1))][ki][kj - 1]);
                    }
                }
            }
        }
    }
};
auto ST_query = [&](int x1, int y1, int x2, int y2) -> int {
    int ki = Log2[x2 - x1 + 1], kj = Log2[y2 - y1 + 1];
    int t1 = f[x1][y1][ki][kj];
    int t2 = f[x2 - (1 << ki) + 1][y1][ki][kj];
    int t3 = f[x1][y2 - (1 << kj) + 1][ki][kj];
    int t4 = f[x2 - (1 << ki) + 1][y2 - (1 << kj) + 1][ki][kj];
    return std::max({t1, t2, t3, t4});
};

```

