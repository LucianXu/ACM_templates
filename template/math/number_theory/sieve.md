# 积性函数

## 素数
```cpp
vi prime, is_prime(n + 1, 1);
auto Euler_sieve = [&](int n){
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) prime.push_back(i);
        for (auto p : prime) {
            if (i * p > n) break;
            is_prime[i * p] = 0;
            if (i % p == 0) break;
        }
    }
};
```

## $\varphi(n)$

$$
\varphi(n)为欧拉函数
$$

```cpp
vi phi(n + 1), prime;
vi is_prime(n + 1, 1);
auto get_phi = [&](int n) {
    int cnt = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prime) {
            if (i * p > n) break;
            is_prime[i * p] = 0;
            if (i % p) {
                phi[i * p] = phi[i] * phi[p];
            } else {
                phi[i * p] = phi[i] * p;
                break;
            }
        }
    }
};
```

## $d(n)$

$$
d(n) = \sum_{k | n} k
$$

```cpp
vi g(n + 1), d(n + 1), prime;
vi is_prime(n + 1, 1);
auto get_d = [&](int n) {
    int tot = 0;
    g[1] = d[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            d[i] = g[i] = i + 1;
        }
        for (auto p : prime) {
            if (i * p > n) break;
            is_prime[i * p] = 0;
            if (i % p == 0) {
                g[i * p] = g[i] * p + 1;
                d[i * p] = d[i] / g[i] * g[i * p];
                break;
            } else {
                d[i * p] = d[i] * d[p];
                g[i * p] = 1 + p;
            }
        }
    }
};
```

## $\mu(n)$

$$
\mu(n)为莫比乌斯函数
$$

```cpp
vi mu(n + 1), prime;
vi is_prime(n + 1, 1);
auto get_mu = [&](int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto p : prime) {
            if (i * p > n) break;
            is_prime[i * p] = 0;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
};
```

