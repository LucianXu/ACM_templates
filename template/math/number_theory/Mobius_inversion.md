# 莫比乌斯反演

## 莫比乌斯函数

$$
\mu(n) = \begin{cases}1&n=1\\0&n \text{ 含有平方因子\ }\\(-1)^k&k \text{ 为\ } n \text{ 的本质不同素因子个数\ }\end{cases}
$$

## 性质

$$
\sum_{d|n}\mu(d) = \begin{cases}1&n=1\\0&n\neq1\end{cases}
$$

反演结论
$$
[gcd(i, j) = 1] = \sum_{d|gcd(i, j)}\mu(d)
$$
$O(n \log n)$ 求莫比乌斯函数

```CPP
mu[1] = 1;
for(int i = 1; i <= N; i++){
    for(int j = i + i; j <= N; j += i){
        mu[j] -= mu[i];
    }
}
```

$$
\varphi(n) = \sum_{d|n}d \cdot \mu(\frac{n}{d})
$$

## 莫比乌斯变换

设$f(n)$，$F(n)$。

1. $F(n) = \sum_{d|n}f(d)$，则 $f(n) = \sum_{d|n}\mu(d)F(\frac{n}{d})$。
2. $F(n) = \sum_{n|d}f(d)$，则 $f(n) = \sum_{n|d}\mu(\frac{d}{n})F(d)$。
