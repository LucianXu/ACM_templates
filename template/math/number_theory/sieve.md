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

## 杜教筛

```cpp
const int N = 1e7;
vi mu(N + 1), phi(N + 1), prime;
vl sum_phi(N + 1), sum_mu(N + 1);
vi is_prime(N + 1, 1);
std::map<LL, LL> mp_mu;

/* 计算 1 ~ 10^7 的 mu */
auto get_mu = [&](int n) {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (auto p : prime) {
            if (i * p > n) break;
            is_prime[i * p] = 0;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                break;
            }
            phi[i * p] = phi[i] * phi[p];
            mu[i * p] = -mu[i];
        }
    }
};
get_mu(N);
for (int i = 1; i <= N; i++) {
    sum_phi[i] = sum_phi[i - 1] + phi[i];
    sum_mu[i] = sum_mu[i - 1] + mu[i];
}

/* 杜教筛: 求 mu 的前缀和 */
std::function<LL(LL)> S_mu = [&](LL x) -> LL {
    if (x <= N) return sum_mu[x];
    auto it = mp_mu.find(x);
    if (it != mp_mu.end()) return mp_mu[x];
    LL ans = 1;
    for (LL i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ans -= S_mu(x / i) * (j - i + 1);
    }
    return mp_mu[x] = ans;
};

/* 杜教筛: 求 phi 的前缀和 */
auto S_phi = [&](LL x) -> LL {
    if (x <= N) return sum_phi[x];
    LL ans = 0;
    for (LL i = 1, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ans += 1ll * (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
    }
    return (ans - 1) / 2 + 1;
};
```

