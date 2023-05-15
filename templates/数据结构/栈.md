# 栈

## 单调栈

维护单调下降序列。

```cpp
for (int i = 1; i <= n; i++){
    while (!stk.empty() and stk.back() > a[i]) {
      stk.pop_back();
    }
    stk.pop_back(a[i]);
}
```

