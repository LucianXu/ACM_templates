# 队列

## 单调队列（滑动窗口）

维护长度不超过 $k$ 的单调下降的序列。

```cpp
std::deque<int> q;
for (int i = 1; i <= n; i++) {    
    while (!q.emprty and a[q.back()] >= a[i]) p.pop_back();
    if (!q.emprty() and i - q.front() >= k) q.pop_front();
    q.push_back(i);
}
```

