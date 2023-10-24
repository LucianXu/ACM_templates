auto halfPlain = [&](std::vector<line>& ln) -> std::vector<point> {
    std::sort(all(ln));
    ln.erase(
        unique(
            all(ln),
            [](line& p, line& q) {
                double t1 = std::atan2((p.b - p.a).y, (p.b - p.a).x);
                double t2 = std::atan2((q.b - q.a).y, (q.b - q.a).x);
                return fabs((t1 - t2)) < eps;
            }),
        ln.end());
    auto check = [&](line p, line q, line r) -> bool {
        point a = iPoint(p, q);
        return ((r.b - r.a) ^ (a - r.a)) < -eps;
    };
    line q[ln.size() + 2];
    int hh = 1, tt = 0;
    q[++tt] = ln[0];
    q[++tt] = ln[1];
    for (int i = 2; i < (int) ln.size(); i++) {
        while (hh < tt and check(q[tt - 1], q[tt], ln[i])) tt--;
        while (hh < tt and check(q[hh + 1], q[hh], ln[i])) hh++;
        q[++tt] = ln[i];
    }
    while (hh < tt and check(q[tt - 1], q[tt], q[hh])) tt--;
    while (hh < tt and check(q[hh + 1], q[hh], q[tt])) hh++;
    q[tt + 1] = q[hh];
    std::vector<point> ans;
    for (int i = hh; i <= tt; i++) {
        ans.push_back(iPoint(q[i], q[i + 1]));
    }
    return ans;
};
