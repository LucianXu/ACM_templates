# BSGS & exBSGS

求解满足 $a ^ x \equiv b \bmod p$ 的 $x$

```cpp
/* return value = -1e18 means no solution */
auto BSGS = [&](LL a, LL b, LL p) {
    if (1 % p == b % p) return 0ll;
    LL k = std::sqrt(p) + 1;
    std::unordered_map<LL, LL> hash
    for (LL i = 0, j = b % p; i < k; i++) {
        hash[j] = i;
        j = j * a % p;
    }
    LL ak = 1;
    for (int i = 1; i <= k; i++) ak = ak * a % p;
    for (int i = 1, j = ak; i <= k; i++) {
        if (hash.count(j)) return 1ll * i * k - hash[j];
        j = 1ll * j * ak % p;
    }
    return -INF;
};
```

$(a, p) \neq 1$ 的情形

```cpp
/* return value < 0 means no solution */
auto exBSGS = [&](auto&& self, LL a, LL b, LL p) {
    b = (b % p + p) % p;
    if (1ll % p == b % p) return 0ll;
    LL x, y, d = std::gcd(a, p);
    exgcd(exgcd, a, p, x, y);
    if (d > 1) {
        if (b % d != 0) return -INF;
        exgcd(exgcd, a / d, p / d, x, y);
        return self(self, a, b / d * x % (p / d), p / d) + 1;
    }
    return BSGS(a, b, p);
};
```

