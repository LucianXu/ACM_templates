# Stirling 数

## 第一类 Stirling 数

记作 $s(n, k)$ 或者 $\left[ \frac{n}{k} \right]$。

表示将 $n$ 个两两不同的元素划分成 $k$ 个圆排列的方案数。

递推式
$$
s(n, k) = s(n - 1, k - 1) + (n - 1) \ s(n - 1, k), \\
where \ s(n, 0) = [n = 0].
$$

## 第二类 Stirling 数

记作 $S(n, k)$ 或者 $\left \{ \frac{n}{k} \right \}$。

表示将$n$个两两不同的元素划分为 $k$ 个互不相交的非空子集的方案数。

递推式
$$
S(n, k) = S(n - 1, k - 1) + k \ S(n - 1, k), \\
where \ S(n, 0) = [n = 0].
$$
