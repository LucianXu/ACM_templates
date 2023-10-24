# 数论分块

## 分块的逻辑

### 下取整 $\lfloor \frac{n}{g} \rfloor = k$ 的分块（$g \leqslant n$）

```
for(int l = 1, r, k; l <= n; l = r + 1){
    k = n / l;
    r = n / (n / l);
    debug(l, r, k);
}
```

$k = \lfloor \frac{n}{g} \rfloor$ 从大到小遍历 $\lfloor \frac{n}{g} \rfloor$ 的所有取值，$[l, \ r]$ 对应的是 $g$ 取值的区间。

下面是 debug 结果。

```cpp
// n = 11
[l, r, k] : 1 1 11 
[l, r, k] : 2 2 5 
[l, r, k] : 3 3 3 
[l, r, k] : 4 5 2 
[l, r, k] : 6 11 1 

```

### 上取整 $\lceil \frac{n}{g} \rceil = k$ 的分块（$g < n$）

```
for(int l = 1, r, k; l < n; l = r + 1){
    k = (n + l - 1) / l;
    r = (n + k - 2) / (k - 1) - 1;
    debug(l, r, k);
}
```

$k = \lceil \frac{n}{g} \rceil$ 从大到小遍历 $\lceil \frac{n}{g} \rceil$ 的所有取值，$[l, \ r]$ 对应的是 $g$ 取值的区间。

下面是 debug 结果。

```cpp
// n = 11
[l, r, k] : 1 1 11 
[l, r, k] : 2 2 6 
[l, r, k] : 3 3 4 
[l, r, k] : 4 5 3 
[l, r, k] : 6 10 2 
```

## 一般形式

$\sum_{i=1}^n f(i)\lfloor \frac{n}{i} \rfloor$

设 $s(i)$ 为 $f(i)$ 的前缀和。

```cpp
for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (s[r] - s[l - 1]) * (n / l);
}
```

$\sum_{i = 1}^{n}f(i){\lfloor{\frac{a}{i}}\rfloor\lfloor{\frac{b}{i}}\rfloor}$

```cpp
for (int l = 1, r, r1, r2; l <= n; l = r + 1) {
    if (a / l) {
        r1 = a / (a / l);
    } else {
        r1 = n;
    }
    if (b / l) {
        r2 = b / (b / l);
    } else {
        r2 = n;
    }
    r = min(min(r1, r2), n);
    ans += (s[r] - s[l - 1]) * (a / l) * (b / l);
}
```



