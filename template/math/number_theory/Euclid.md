# 欧几里得算法

## 欧几里得算法

```c++
std::gcd(a, b)
```

## 扩展欧几里得算法

```C++
auto exgcd = [&](LL a, LL b, LL& x, LL& y) {
    LL x1 = 1, x2 = 0, x3 = 0, x4 = 1;
    while (b != 0) {
        LL c = a / b;
        std::tie(x1, x2, x3, x4, a, b) =
            std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
    }
    x = x1, y = x2;
};
```

```cpp
auto exgcd = [&](auto&& self, LL a, LL b, LL& x, LL& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    self(self, b, a % b, y, x);
    y -= a / b * x;
};
```

```cpp
auto exgcd = [&](auto&& self, LL a, LL b, LL& x, LL& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    LL d = self(self, b, a % b, y, x);
    y -= a / b * x;
    return d;
};
```

## 类欧几里得算法

一般形式：求 $f(a, b, c, n) = \sum\limits_{i = 0}^{n}\lfloor{\frac{ai+b}{c}}\rfloor$​

$f(a, b, c, n)$​ 可以单独求。

$f(a, b, c, n) = nm-f(c, c - b - 1, a, m - 1)$

```c++
LL f(LL a, LL b, LL c, LL n) {
    if (a == 0) return ((b / c) * (n + 1));
    if (a >= c || b >= c)
        return f(a % c, b % c, c, n) + (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1);
    LL m = (a * n + b) / c;
    LL v = f(c, c - b - 1, a, m - 1);
    return n * m - v;
}
```

更进一步，求：$g(a, b, c, n) = \sum\limits_{i = 0}^{n}i\lfloor{\frac{ai+b}{c}}\rfloor$ 以及 $h(a, b, c, n) = \sum\limits_{i = 0}^{n}{\lfloor{\frac{ai+b}{c}}\rfloor}^2$​

直接记吧。

$g(a, b, c, n) = \lfloor{\frac{mn(n+1)-f(c, c-b-1, a, m-1)-h(c, c-b-1, a, m-1)}{2}}\rfloor$​

$h(a, b, c, n) = nm(m+1)-2f(c, c - b-1, a, m- 1)-2g(c,c-b-1,a,m-1)-f(a, b, c, n)$

```c++
const int inv2 = 499122177;
const int inv6 = 166374059;

LL f(LL a, LL b, LL c, LL n);
LL g(LL a, LL b, LL c, LL n);
LL h(LL a, LL b, LL c, LL n);

struct data {
    LL f, g, h;
};

data calc(LL a, LL b, LL c, LL n) {
    LL ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
    data d;
    if (a == 0) {
        d.f = bc * n1 % mod;
        d.g = bc * n % mod * n1 % mod * inv2 % mod;
        d.h = bc * bc % mod * n1 % mod;
        return d;
    }
    if (a >= c || b >= c) {
        d.f = n * n1 % mod * inv2 % mod * ac % mod + bc * n1 % mod;
        d.g =
            ac * n % mod * n1 % mod * n21 % mod * inv6 % mod + bc * n % mod * n1 % mod * inv2 % mod;
        d.h = ac * ac % mod * n % mod * n1 % mod * n21 % mod * inv6 % mod +
              bc * bc % mod * n1 % mod + ac * bc % mod * n % mod * n1 % mod;
        d.f %= mod, d.g %= mod, d.h %= mod;
        data e = calc(a % c, b % c, c, n);
        d.h += e.h + 2 * bc % mod * e.f % mod + 2 * ac % mod * e.g % mod;
        d.g += e.g, d.f += e.f;
        d.f %= mod, d.g %= mod, d.h %= mod;
        return d;
    }
    data e = calc(c, c - b - 1, a, m - 1);
    d.f = n * m % mod - e.f, d.f = (d.f % mod + mod) % mod;
    d.g = m * n % mod * n1 % mod - e.h - e.f, d.g = (d.g * inv2 % mod + mod) % mod;
    d.h = n * m % mod * (m + 1) % mod - 2 * e.g - 2 * e.f - d.f;
    d.h = (d.h % mod + mod) % mod;
    return d;
}
```

