# DSU

```c++
vi fa(n + 1);
std::iota(all(fa), 0);
std::function<void(int)> find = [&] (int x) -> int{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
};
auto merge = [&] (int x, int y) -> void{
    x = find(x), y = find(y);
    if (x == y) return;
    // operations //
    fa[y] = x;
};

```

