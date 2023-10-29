# 卢卡斯定理

## 卢卡斯定理

用于求大组合数，并且模数是一个不大的素数。

$\left(\begin{array}{}n \\ m\end{array}\right) \bmod p=\left(\begin{array}{}{\lfloor n / p\rfloor} \\ {\lfloor m / p\rfloor}\end{array}\right) \cdot\left(\begin{array}{}n \bmod p \\ m \bmod p\end{array}\right) \bmod p$

$\left(\begin{array}{}n \bmod p \\ m \bmod p\end{array}\right)$ 可以直接计算，$\left(\begin{array}{}{\lfloor n / p\rfloor} \\ {\lfloor m / p\rfloor}\end{array}\right) $ 可以继续使用卢卡斯计算。

当 $m = 0$ 的时候，返回 $1$。$p$ 不太大，一般在 $1e5$ 左右。

```c++
auto C = [&](LL n, LL m, LL p) -> LL {
    if (n < m) return 0;
    if (m == 0) return 1;
    return ((fac[n] * inv_fac[m]) % p * inv_fac[n - m]) % p;
};

auto lucas = [&](auto&& self, LL n, LL m, LL p) -> LL {
    if (n < m) return 0;
    if (m == 0) return 1;
    return (C(n % p, m % p, p) * self(self, n / p, m / p, p)) % p;
}
```

## 素数在组合数中的次数

Legengre 给出一种 $n!$ 中素数 $p$ 的幂次的计算方式为： $\sum_{1 \leqslant j} \lfloor \frac{n}{p^j} \rfloor$。

另一种计算方式利用 $p$ 进制下各位数字和：$v_p(n!) = \frac{n - S_p(n)}{p - 1}$。

则有 $v_p(C_m^n) = \frac{S_p(n) + S_p(m - n) - S_p(m)}{p - 1}$。

## 扩展卢卡斯定理

计算 $\left(\begin{array}{}n \\ m\end{array}\right) \bmod M$，$M$ 可能为合数。

第一部分：CRT。

原问题变成求
$$
\left \{
\begin{array}{cl}
\left(\begin{array}{}n \\ m\end{array}\right) \equiv a_1 \bmod p_1^{\alpha_1} \\
\left(\begin{array}{}n \\ m\end{array}\right) \equiv a_2 \bmod p_2^{\alpha_2} \\
\dots \\
\left(\begin{array}{}n \\ m\end{array}\right) \equiv a_k \bmod p_k^{\alpha_k} \\
\end{array}
\right.
$$
在求出 $a_i$ 之后就可以利用CRT求出答案。

第二部分：移除分子分母中的素数

问题转换成求解$\left(\begin{array}{}n \\ m\end{array}\right) \bmod q^k$。等价于
$$
\frac{\frac{n!}{q^x}}{\frac{m!}{q^y}\frac{(n - m)!}{q^z}} q^{x - y - z} \bmod q^k
$$
其中 $x$ 表示 $n!$ 中 $q$ 的次数，$y$，$z$ 同理。

第三部分：威尔逊定理的推论

问题转换为求 $\frac{n!}{q^x} \bmod q^k$ 。可以利用威尔逊定理的推论。

```cpp
auto func = [&](auto&& self, LL n, LL pi, LL pk) {
    if (!n) return 1ll;
    LL ans = 1;
    for (LL i = 2; i <= pk; i++) {
        if (i % pi) ans = ans * i % p;
    }
    ans = quick_power(ans, n / pk, pk);
    for (LL i = 2; i <= n % pk; i++) {
        if (i % pi) ans = ans * i % pk;
    }
    ans = ans * self(self, n / pi, pi, pk) % pk;
    return ans;
};

auto multiLucas = [&](LL n, LL m, LL pi, LL pk) {
    LL cnt = 0;
    for (LL i = n; i; i /= pi) cnt += i / pi;
    for (LL i = m; i; i /= pi) cnt -= i / pi;
    for (LL i = n - m; i; i /= pi) cnt -= i / pi;
    LL ans = quick_power(pi, cnt, pk) * func(func, n, pi, pk) % pk;
    ans = ans * inv(func(func, m, pi, pk), pk) % pk;
    ans = ans * inv(func(func, n - m, pi, pk), pk) % pk;
    return ans;
};

auto crt = [&](const vl& a, const vl& m, int k) {
    LL ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + a[i] * inv(p / m[i], m[i]) * (p / m[i])) % p;
    }
    return (ans % p + p) % p;
};

auto exLucas = [&](LL n, LL m, LL p) {
    vl a, prime;
    for (int i = 2; i * i <= p; i++) {
        if (p % i) continue;
        prime.push_back(1);
        while (p % i == 0) {
            prime.back() *= i;
            p /= i;
        }
        a.push_back(multiLucas(n, m, i, prime.back()));
    }
    if (p > 1) {
        prime.push_back(p);
        a.push_back(multiLucas(n, m, p, p));
    }
    return crt(a, prime, a.size());
};
```

