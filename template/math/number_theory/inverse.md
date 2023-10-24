# 逆元

## 线性递推

$a^{-1} \equiv -\lfloor\frac{p}{a}\rfloor\times(p\%a)^{-1}$

```c++
vi inv(n + 1);
auto sieve_inv = [&](int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    }
};
```

## 求 $n$ 个数的逆元

```cpp
auto get_inv =[&](const vi& a) {
    int n = a.size();
    vi b(n), f(n), ivf(n);
    f[0] = a[0];
    for (int i = 1; i < n; i++) {
        f[i] = 1ll * f[i - 1] * a[i] % p;
    }
    ivf.back() = quick_power(f.back(), p - 2, p);
    for (int i = n - 1; i; i--) {
        ivf[i - 1] = 1ll * ivf[i] * a[i] % p;
    }
    b[0] = ivf[0];
    for (int i = 1; i < n; i++) {
        b[i] = 1ll * ivf[i] * f[i - 1] % p;
    }
    return b;
};
```
