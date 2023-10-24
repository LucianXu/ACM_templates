# FWT

## and

$$
C_i = \sum\limits_{i = j \& k} A_j B_k
$$

分治过程
$$
\operatorname{FWT[A]} = merge(\operatorname{FWT[A_0]} + \operatorname{FWT[A_1]}, \operatorname{FWT[A_1]}), \\
\operatorname{UFWT[A']} = merge(\operatorname{UFWT[A'_0]} - \operatorname{UFWT[A'_1]}, \operatorname{UFWT[A'_1]}).
$$

```cpp
// mod 998244353 //
auto FWT_and = [&](vi v, int type) -> vi {
    int n = v.size();
    for (int mid = 1; mid < n; mid <<= 1) {
        for (int block = mid << 1, j = 0; j < n; j += block) {
            for (int i = j; i < j + mid; i++) {
                LL x = v[i], y = v[i + mid];
                if (type == 1) {
                    v[i] = add(x, y);
                } else {
                    v[i] = sub(x, y);
                }
            }
        }
    }
    return v;
};
```

## or

$$
C_i = \sum\limits_{i = j \mid k} A_j B_k
$$

分治过程
$$
\operatorname{FWT[A]} = merge(\operatorname{FWT[A_0]}, \operatorname{FWT[A_0]} + \operatorname{FWT[A_1]}), \\
\operatorname{UFWT[A']} = merge(\operatorname{UFWT[A'_0]}, -\operatorname{UFWT[A'_0]} + \operatorname{UFWT[A'_1]}).
$$

```cpp
// mod 998244353 //
auto FWT_or = [&](vi v, int type) -> vi {
    int n = v.size();
    for (int mid = 1; mid < n; mid <<= 1) {
        for (int block = mid << 1, j = 0; j < n; j += block) {
            for (int i = j; i < j + mid; i++) {
                LL x = v[i], y = v[i + mid];
                if (type == 1) {
                    v[i + mid] = add(x, y);
                } else {
                    v[i + mid] = sub(y, x);
                }
            }
        }
    }
    return v;
};
```

## xor

$$
C_i = \sum\limits_{i = j \oplus k} A_j B_k
$$

分治过程
$$
\operatorname{FWT[A]} = merge(\operatorname{FWT[A_0]} + \operatorname{FWT[A_1]}, \operatorname{FWT[A_0]} - \operatorname{FWT[A_1]}), \\
\operatorname{UFWT[A']} = merge(\frac{\operatorname{UFWT[A'_0]} + \operatorname{UFWT[A'_1]}}{2}, \frac{\operatorname{UFWT[A'_0]} - \operatorname{UFWT[A'_1]}}{2}).
$$

```cpp
// mod 998244353 //
auto FWT_xor = [&](vi v, int type) -> vi {
    int n = v.size();
    for (int mid = 1; mid < n; mid <<= 1) {
        for (int block = mid << 1, j = 0; j < n; j += block) {
            for (int i = j; i < j + mid; i++) {
                LL x = v[i], y = v[i + mid];
                v[i] = add(x, y);
                v[i + mid] = sub(x, y);
                if (type == -1) {
                    Mul(v[i], inv2);
                    Mul(v[i + mid], inv2);
                }
            }
        }
    }
    return v;
};

```

统一地，

```cpp
a = FWT(a, 1),  b = FWT(b, 1);
for (int i = 0; i < (1 << n); i++) {
    c[i] = mul(a[i], b[i]);
}
c = FWT(c, -1);
```

