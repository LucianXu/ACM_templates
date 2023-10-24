# Miller Rabin 素性检验

原理基于：对奇素数 $p$，$a^2 \equiv 1 \bmod p$ 的解为 $x \equiv 1 \bmod p$ 或 $x \equiv p - 1 \bmod p$，以及费马小定理。

随机一个底数 $x$，将 $a ^ {p - 1} \bmod p$ 的指数 $p - 1$ 分解为 $a \times 2^b$，计算出 $x^a$，之后进行最多 $b$ 次平方操作，若发现非平凡平方根时即可判断出其不是素数，否则通过此轮测试。

$test\_time$ 为测试次数，建议设为不小于 $8$ 的整数以保证正确率，但也不宜过大，否则会影响效率。

```cpp
auto miller_rabin = [&](LL n) -> bool {
    if (n <= 3) return n == 2 || n == 3;
    LL a = n - 1, b = 0;
    while (!(a & 1)) a >>= 1, b++;
    for (int i = 1, j; i <= 10; i++) {    // test_time = 10;
        LL x = rand() % (n - 2) + 2, v = quick_power(x, a, n);
        if (v == 1 || v == n - 1) continue;
        for (j = 0; j < b; j++) {
            if (v == n - 1) break;
            v = (i28) v * v % n;
        }
        if (j >= b) return false;
    }
    return true;
};
```

事实上底数没必要随机 $10$ 次，检验如下数即可。快速幂记得也要 __int128。

1. $int$ 范围：$2$，$7$，$61$。
2. $long \ long$ 范围：$2$，$325$，$9375$，$28178$，$450775$，$9780504$，$1795265022$。

```cpp
vl vv = {2, 3, 5, 7, 11, 13, 17, 23, 29};

auto miller_rabin = [&](LL n) -> bool {
    auto test = [&](LL n, int a) {
        if (n == a) return true;
        if (n % 2 == 0) return false;
        LL d = (n - 1) >> __builtin_ctzll(n - 1);
        LL r = quick_power(a, d, n);
        while (d < n - 1 and r != 1 and r != n - 1) {
            d <<= 1;
            r = (i128) r * r % n;
        }
        return r == n - 1 or d & 1;
    };
    if (n == 2 or n == 3) return true;
    for (auto p : vv) {
        if (test(n, p) == 0) return false;
    }
    return true;
}
```

