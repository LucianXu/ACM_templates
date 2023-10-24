# 拉格朗日插值

## 一般的插值

给出一个多项式 $f(x)$ 上的 $n$ 个点 $(x_i, y_i)$，求 $f(k)$。

拉格朗日插值的结果是
$$
f(x) = \sum_{i=1}^{n} y_i \prod_{j \neq i} \frac{x - x_j}{x_i - x_j},
$$
直接带入 $k$ 并且取模即可，时间复杂度 $O(n^2)$。

```cpp
std::cin >> n >> k;
std::vector<LL> x(n + 1), y(n + 1);
for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
for (int i = 1; i <= n; i++) {
    LL s1 = y[i] % mod, s2 = 1LL;
    for (int j = 1; j <= n; j++) {
        if (i != j) {
            s1 = s1 * (k - x[j]) % mod;
            s2 = s2 * (x[i] - x[j]) % mod;
        }
    }
    ans += s1 * quick_power(s2, mod - 2, mod) % mod;
    ans = (ans + mod) % mod;
}
```

## 坐标连续的插值

给出的点是 $(i, y_i)$。
$$
\begin{aligned}
& f(x) = \sum_{i=1}^{n} y_i \prod_{j \neq i} \frac{x - x_j}{x_i - x_j} \\
& = \sum_{i=1}^{n} y_i \prod_{j \neq i} \frac{x - j}{i - j} \\
& = \sum_{i=1}^{n} y_i \cdot \frac{\prod\limits_{j=1}^n (x - j)}{(x - i) (-1)^{n+1-i}(i-1)!(n+1-i)!} \\
& = \left( \prod_{j=1}^n (x - j) \right) \left(\sum_{i=1}^n \frac{(-1)^{n+1-i}y_i}{(x-i)(i-1)!(n+1-i)!}\right),
\end{aligned}
$$
时间复杂度为 $O(n)$。
