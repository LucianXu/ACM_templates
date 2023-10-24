# 笛卡尔树

一种特殊的平衡树，用元素的值作为平衡点节点的 $val$，元素的下标作为 $key$。

<img src="https://oi-wiki.org/ds/images/cartesian-tree1.png" alt="eg" style="zoom: 67%;" />

```cpp
// cartesian tree //
vi ls(n + 1), rs(n + 1), stk(n + 1);
int top = 1;
for (int i = 1; i <= n; i++) {
    int k = top;
    while (k and a[stk[k]] > a[i]) k--;
    if (k) rs[stk[k]] = i;
    if (k < top) ls[i] = stk[k + 1];
    stk[++k] = i;
    top = k;
}
```

