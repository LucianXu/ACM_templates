# Pollard-Rho 算法

能在 $O(n^{\frac{1}{4}})$ 的时间复杂度随机出一个 $n$ 的非平凡因数。

通过 $x_{i+1} = (x_i^2 + c) \bmod n$ 生成一个随机数序列，其中 $c$ 是随机选取的。显然 $\{x_n\}$ 中数的种类是有限的，在个数足够多之后会进入循环。

## 倍增实现

```cpp
auto pollard_rho = [&](LL x) -> LL{
    LL s = 0, t = 0, val = 1;
    LL c = rand() % (x - 1) + 1;
    for(int goal = 1;; goal <<= 1, s = t, val = 1){
        for(int step = 1; step <= goal; step++){
            t = ((i128) t * t + c) % x;
            val = (i128) val * abs(t - s) % x;
            if(step % 127 == 0){
                LL d = std::gcd(val, x);
                if(d > 1) return d;
            }
        }
        LL d = std::gcd(val, x);
        if(d > 1) return d;
    }
};
```

## 利用 Miller-Rabin 和 Pollard-Rho 进行素因数分解

```cpp
auto factorize = [&](LL a) -> vl{
    vl ans, stk;
    for (auto p : prime) {
        if (p > 1000) break;
        while (a % p == 0) {
            ans.push_back(p);
            a /= p;
        }
        if (a == 1) return ans;
    }
    // 先筛小素数，再跑 Pollard-Rho //
    stk.push_back(a);
    while (!stk.empty()) {
        LL b = stk.back();
        stk.pop_back();
        if (miller_rabin(b)) {
            ans.push_back(b);
            continue;
        }
        LL c = b;
        while (c >= b) c = pollard_rho(b);
        stk.push_back(c);
        stk.push_back(b / c);
    }
    return ans;
};
```

