# 博弈论

## Nim 游戏

若 Nim 和为 0 , 则先手必败.

暴力打表。

```cpp
vi SG(21, -1); /* 记忆化 */
std::function<int(int, int)> sg = [&](int x) -> int {
    if (/* 为最终态 */) return SG[x] = 0;
    if (SG[x] != -1) return SG[x];
    vi st;
    for (/* 枚举所有可到达的状态 y */) {
        st.push_back(sg(y));
    }
    std::sort(all(st));
    for (int i = 0; i < st.size(); i++) {
        if (st[i] != i) return SG[x] = i;
    }
    return SG[x] = st.size();
};
```

## anti-Nim 游戏

若

1. 所有堆的石子均为一个, 且 Nim 和不为 0, 
2. 至少有一堆石子超过一个, 且 Nim 和为 0,

则先手必败.
