# class Polynomial

```cpp
class polynomial : public vi {
   public:
    polynomial() = default;
    polynomial(const vi& v) : vi(v) {}
    polynomial(vi&& v) : vi(std::move(v)) {}

    int degree() { return size() - 1; }

    void clearzero() {
        while (size() && !back()) pop_back();
    }
};


polynomial& operator+=(polynomial& a, const polynomial& b) {
    a.resize(std::max(a.size(), b.size()), 0);
    for (int i = 0; i < b.size(); i++) {
        Add(a[i], b[i]);
    }
    a.clearzero();
    return a;
}

polynomial operator+(const polynomial& a, const polynomial& b) {
    polynomial ans = a;
    return ans += b;
}

polynomial& operator-=(polynomial& a, const polynomial& b) {
    a.resize(std::max(a.size(), b.size()), 0);
    for (int i = 0; i < b.size(); i++) {
        Sub(a[i], b[i]);
    }
    a.clearzero();
    return a;
}

polynomial operator-(const polynomial& a, const polynomial& b) {
    polynomial ans = a;
    return ans -= b;
}

class ntt_t {
   public:
    static const int maxbit = 22;
    static const int sz = 1 << maxbit;
    static const int mod = 998244353;
    static const int g = 3;

    std::array<int, sz + 10> w;
    std::array<int, maxbit + 10> len_inv;

    ntt_t() {
        int wn = pow(g, (mod - 1) >> maxbit);
        w[0] = 1;
        for (int i = 1; i <= sz; i++) {
            w[i] = mul(w[i - 1], wn);
        }
        len_inv[maxbit] = pow(sz, mod - 2);
        for (int i = maxbit - 1; ~i; i--) {
            len_inv[i] = add(len_inv[i + 1], len_inv[i + 1]);
        }
    }

    void operator()(vi& v, int& n, int type) {
        int bit = 0;
        while ((1 << bit) < n) bit++;
        int tot = (1 << bit);
        v.resize(tot, 0);
        vi rev(tot);
        n = tot;
        for (int i = 0; i < tot; i++) {
            rev[i] = rev[i >> 1] >> 1;
            if (i & 1) {
                rev[i] |= tot >> 1;
            }
        }
        for (int i = 0; i < tot; i++) {
            if (i < rev[i]) {
                std::swap(v[i], v[rev[i]]);
            }
        }
        for (int midd = 0; (1 << midd) < tot; midd++) {
            int mid = 1 << midd;
            int len = mid << 1;
            for (int i = 0; i < tot; i += len) {
                for (int j = 0; j < mid; j++) {
                    int w0 = v[i + j];
                    int w1 = mul(
                        w[type == 1 ? (j << maxbit - midd - 1) : (len - j << maxbit - midd - 1)],
                        v[i + j + mid]);
                    v[i + j] = add(w0, w1);
                    v[i + j + mid] = sub(w0, w1);
                }
            }
        }
        if (type == -1) {
            for (int i = 0; i < tot; i++) {
                v[i] = mul(v[i], len_inv[bit]);
            }
        }
    }
} NTT;
```

## 乘法

```cpp
polynomial& operator*=(polynomial& a, const polynomial& b) {
    if (!a.size() || !b.size()) {
        a.resize(0);
        return a;
    }
    polynomial tmp = b;
    int deg = a.size() + b.size() - 1;
    int temp = deg;

    // 项数较小直接硬算

    if ((LL) a.size() * (LL) b.size() <= (LL) deg * 50LL) {
        tmp.resize(0);
        tmp.resize(deg, 0);
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                tmp[i + j] = add(tmp[i + j], mul(a[i], b[j]));
            }
        }
        a = tmp;
        return a;
    }

    // 项数较多跑 NTT

    NTT(a, deg, 1);
    NTT(tmp, deg, 1);
    for (int i = 0; i < deg; i++) {
        Mul(a[i], tmp[i]);
    }
    NTT(a, deg, -1);
    a.resize(temp);
    return a;
}

polynomial operator*(const polynomial& a, const polynomial& b) {
    polynomial ans = a;
    return ans *= b;
}
```

## 逆

```c++
polynomial inverse(const polynomial& a) {
    polynomial ans({pow(a[0], mod - 2)});
    polynomial temp;
    polynomial tempa;
    int deg = a.size();
    for (int i = 0; (1 << i) < deg; i++) {
        tempa.resize(0);
        tempa.resize(1 << i << 1, 0);
        for (int j = 0; j != tempa.size() and j != deg; j++) {
            tempa[j] = a[j];
        }
        temp = ans * (polynomial({2}) - tempa * ans);
        if (temp.size() > (1 << i << 1)) {
            temp.resize(1 << i << 1, 0);
        }
        temp.clearzero();
        std::swap(temp, ans);
    }
    ans.resize(deg);
    return ans;
}
```

## 对数

```cpp
polynomial diffrential(const polynomial& a) {
    if (!a.size()) {
        return a;
    }
    polynomial ans(vi(a.size() - 1));
    for (int i = 1; i < a.size(); i++) {
        ans[i - 1] = mul(a[i], i);
    }
    return ans;
}

polynomial integral(const polynomial& a) {
    polynomial ans(vi(a.size() + 1));
    for (int i = 0; i < a.size(); i++) {
        ans[i + 1] = mul(a[i], pow(i + 1, mod - 2));
    }
    return ans;
}

polynomial ln(const polynomial& a) {
    int deg = a.size();
    polynomial da = diffrential(a);
    polynomial inva = inverse(a);
    polynomial ans = integral(da * inva);
    ans.resize(deg);
    return ans;
}
```

## 指数

```cpp
polynomial exp(const polynomial& a) {
    polynomial ans({1});
    polynomial temp;
    polynomial tempa;
    polynomial tempaa;
    int deg = a.size();
    for (int i = 0; (1 << i) < deg; i++) {
        tempa.resize(0);
        tempa.resize(1 << i << 1, 0);
        for (int j = 0; j != tempa.size() and j != deg; j++) {
            tempa[j] = a[j];
        }
        tempaa = ans;
        tempaa.resize(1 << i << 1);
        temp = ans * (tempa + polynomial({1}) - ln(tempaa));
        if (temp.size() > (1 << i << 1)) {
            temp.resize(1 << i << 1, 0);
        }
        temp.clearzero();
        std::swap(temp, ans);
    }
    ans.resize(deg);
    return ans;
}
```

## 开根号

```cpp
polynomial sqrt(polynomial& a) {
    polynomial ans({cipolla(a[0])});
    if (ans[0] == -1) return ans;
    polynomial temp;
    polynomial tempa;
    polynomial tempaa;
    int deg = a.size();
    for (int i = 0; (1 << i) < deg; i++) {
        tempa.resize(0);
        tempa.resize(1 << i << 1, 0);
        for (int j = 0; j != tempa.size() and j != deg; j++) {
            tempa[j] = a[j];
        }
        tempaa = ans;
        tempaa.resize(1 << i << 1);
        temp = (tempa * inverse(tempaa) + ans) * inv2;
        if (temp.size() > (1 << i << 1)) {
            temp.resize(1 << i << 1, 0);
        }
        temp.clearzero();
        std::swap(temp, ans);
    }
    ans.resize(deg);
    return ans;
}

// 特判 //

int cnt = 0;
for (int i = 0; i < a.size(); i++) {
    if (a[i] == 0) {
        cnt++;
    } else {
        break;
    }
}
if (cnt) {
    if (cnt == n) {
        for (int i = 0; i < n; i++) {
            std::cout << "0 ";
        }
        std::cout << endl;
        return 0;
    }
    if (cnt & 1) {
        std::cout << "-1" << endl;
        return 0;
    }
    polynomial b(vi(a.size() - cnt));
    for (int i = cnt; i < a.size(); i++) {
        b[i - cnt] = a[i];
    }
    a = b;
}
a.resize(n - cnt / 2);
a = sqrt(a);
if (a[0] == -1) {
    std::cout << "-1" << endl;
    return 0;
}
reverse(all(a));
a.resize(n);
reverse(all(a));
```

