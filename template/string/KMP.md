# KMP

这一节的 $string$ 都是从 $0$ 开始计数。

## 计算 $next$ 数组

```cpp
auto get_next = [&](const std::string& s) -> vi {
    int n = s.length();
    vi next(n);
    for (int i = 1; i < n; i++) {
        int j = next[i - 1];
        while (j > 0 and s[i] != s[j]) j = next[j - 1];
        if (s[i] == s[j]) j++;
        next[i] = j;
    }
    return next;
};

```

## 应用

### 在文本串中匹配模式串

求出 $s$ 在 $t$ 中所有出现的位置。

用脏字符连接文本串与模式串跑 KMP 即可。

### 字符串的最小周期

如果周期大于 $1$， $n - next[n-1]$ 是最小周期。

如果周期为 $1$，满足条件：

1. $next[n-1] = n$；
2. $next[n-1] \neq n$，但计算出来的并不是循环节，暴力判断一下。
