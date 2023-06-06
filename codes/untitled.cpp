// Johnson 全源最短路 //

// 负环 //
vl dist1(n + 1);
vi vis(n + 1), cnt(n + 1);
auto spfa = [&]() -> bool {
    std::queue<int> q;
    for (int u = 1; u <= n; u++) {
        q.push(u);
        vis[u] = false;
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (auto [v, w] : e[u]) {
            if (dist1[v] > dist1[u] + w) {
                dist1[v] = dist1[u] + w;
                Max(cnt[v], cnt[u] + 1);
                if (cnt[v] >= n) return true;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
};

// dijkstra //
vl dist2(n + 1);
auto dijkstra = [&](int s) {
    for (int u = 1; u <= n; u++) {
        dist2[u] = 1e9;
        vis[u] = false;
    }
    dist2[s] = 0;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> q;
    q.emplace(0, s);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (const auto& [v, w] : e[u]) {
            if (dist2[v] > d + w) {
                dist2[v] = d + w;
                q.emplace(dist2[v], v);
            }
        }
    }
};

if (spfa()) {
    std::cout << -1 << '\n';
    return;
}
for (int u = 1; u <= n; u++) {
    for (auto& [v, w] : e[u]) {
        w += dist1[u] - dist1[v];
    }
}
for (int u = 1; u <= n; u++) {
    dijkstra(u);
}
