# 中国剩余定理

求解
$$
\left\{\begin{array}{ll}N \equiv a_{1} \bmod m_{1} \\ N \equiv a_{2} \bmod m_{2} \\  \cdots \\ N \equiv a_{n} \bmod m_{n}\end{array}\right.
$$
有 $N \equiv \sum\limits_{i=1}^{k} a_{i} \times \operatorname{inv}\left(\frac{M}{m_{i}}, m_{i}\right) \times\left(\frac{M}{m_{i}}\right)\bmod M$​

```c++
auto crt = [&](int n, const vi& a, const vi& m) -> LL{
    LL ans = 0, M = 1;
    for(int i = 1; i <= n; i++) M *= m[i];
    for(int i = 1; i <= n; i++){
        ans = (ans + a[i] * inv(M / m[i], m[i]) * (M / m[i])) % M;
    }
    return (ans % M + M) % M;
};
```

## 扩展中国剩余定理

```cpp
auto excrt = [&](int n, const vi& a, const vi& m) -> LL{
    LL A = a[1], M = m[1];
    for (int i = 2; i <= n; i++) {
        LL x, y, d = std::gcd(M, m[i]);
        exgcd(M, m[i], x, y);
        LL mod = M / d * m[i];
        x = x * (a[i] - A) / d % (m[i] / d); 
        A = ((M * x + A) % mod + mod) % mod;
        M = mod;
    }
    return A;
};
```

