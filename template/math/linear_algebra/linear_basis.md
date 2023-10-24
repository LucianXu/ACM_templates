### 线性基

```cpp
vi p(35);
auto add_basis = [&](int x) {
    for (int i = 31; i >= 0; i--) {
        if (~(x >> i) & 1) continue;
        if (!p[i]) {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
};
```

