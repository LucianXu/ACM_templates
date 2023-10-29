# 最小割

最小割解决的问题是将图中的点集 $V$ 划分成 $S$ 与 $T$，使得 $S$ 与 $T$ 之间的连边的容量总和最小。

## 最大流最小割定理

网络中 $s$  到 $t$ 的最大流流量的值等于所要求的最小割的值。所以求最小割只需要跑 Dinic 即可。

## 获得 $S$ 中的所有点

在 Dinic 的 $\operatorname{bfs}$ 函数中，每次将所有点的 $d$ 数组值改为无穷大，最后跑完最大流之后 $d$ 数组不为无穷大的就是和源点一起在 $S$ 集合中的点。 

## 例子

最小割的本质是对图中点集进行 $2$-划分，网络流只是求解答案的手段。

1. 在图中花费最小的代价断开一些边使得源点 $s$ 无法流到汇点 $t$

    直接跑最大流就得到了答案。

2. 在图中删除最少的点使得源点 $s$ 无法流到汇点 $t$

    对每个点进行拆点，在 $i$ 与 $i'$ 之间建立容量为 $1$ 的有向边。