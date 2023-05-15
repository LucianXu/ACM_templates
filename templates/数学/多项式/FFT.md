# FFT
## FFT 与拆系数 FFT

```CPP
const int sz = 1 << 23;
int rev[sz];
int rev_n;
void set_rev(int n) {
    if (n == rev_n) return;
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) * n) / 2;
    rev_n = n;
}
tempt void butterfly(T* a, int n) {
    set_rev(n);
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    }
}

namespace Comp {

long double pi = 3.141592653589793238;

tempt struct complex {
    T x, y;
    complex(T x = 0, T y = 0) : x(x), y(y) {}
    complex operator+(const complex& b) const { return complex(x + b.x, y + b.y); }

    complex operator-(const complex& b) const { return complex(x - b.x, y - b.y); }

    complex operator*(const complex& b) const {
        return complex<T>(x * b.x - y * b.y, x * b.y + y * b.x);
    }
    complex operator~() const { return complex(x, -y); }
    static complex unit(long double rad) { return complex(std::cos(rad), std::sin(rad)); }
};

}    // namespace Comp

struct fft_t {
    typedef Comp::complex<double> complex;
    complex wn[sz];

    fft_t() {
        for (int i = 0; i < sz / 2; i++) {
            wn[sz / 2 + i] = complex::unit(2 * Comp::pi * i / sz);
        }
        for (int i = sz / 2 - 1; i; i--) wn[i] = wn[i * 2];
    }

    void operator()(complex* a, int n, int type) {
        if (type == -1) std::reverse(a + 1, a + n);
        butterfly(a, n);
        for (int i = 1; i < n; i *= 2) {
            const complex* w = wn + i;
            for (complex *b = a, t; b != a + n; b += i + 1) {
                t = b[i];
                b[i] = *b - t;
                *b = *b + t;
                for (int j = 1; j < i; j++) {
                    t = (++b)[i] * w[j];
                    b[i] = *b - t;
                    *b = *b + t;
                }
            }
        }
        if (type == 1) return;
        for (int i = 0; i < n * 2; i++) ((double*) a)[i] /= n;
    }
} FFT;

typedef decltype(FFT)::complex complex;

vi fft(const vi& f, const vi& g) {
    static complex ff[sz];
    int n = f.size(), m = g.size();
    vi h(n + m - 1);
    if (std::min(n, m) <= 50) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; ++j) {
                h[i + j] += f[i] * g[j];
            }
        }
        return h;
    }
    int c = 1;
    while (c + 1 < n + m) c *= 2;
    std::memset(ff, 0, sizeof(decltype(*(ff))) * (c));
    for (int i = 0; i < n; i++) ff[i].x = f[i];
    for (int i = 0; i < m; i++) ff[i].y = g[i];
    FFT(ff, c, 1);
    for (int i = 0; i < c; i++) ff[i] = ff[i] * ff[i];
    FFT(ff, c, -1);
    for (int i = 0; i + 1 < n + m; i++) h[i] = std::llround(ff[i].y / 2);
    return h;
}

vi mtt(const vi& f, const vi& g) {
    static complex ff[3][sz], gg[2][sz];
    static int s[3] = {1, 31623, 31623 * 31623};
    int n = f.size(), m = g.size();
    vi h(n + m - 1);
    if (std::min(n, m) <= 50) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Add(h[i + j], mul(f[i], g[j]));
            }
        }
        return h;
    }
    int c = 1;
    while (c + 1 < n + m) c *= 2;
    for (int i = 0; i < 2; ++i) {
        std::memset(ff[i], 0, sizeof(decltype(*(ff[i]))) * (c));
        std::memset(gg[i], 0, sizeof(decltype(*(ff[i]))) * (c));
        for (int j = 0; j < n; ++j) ff[i][j].x = f[j] / s[i] % s[1];
        for (int j = 0; j < m; ++j) gg[i][j].x = g[j] / s[i] % s[1];
        FFT(ff[i], c, 1);
        FFT(gg[i], c, 1);
    }
    for (int i = 0; i < c; ++i) {
        ff[2][i] = ff[1][i] * gg[1][i];
        ff[1][i] = ff[1][i] * gg[0][i];
        gg[1][i] = ff[0][i] * gg[1][i];
        ff[0][i] = ff[0][i] * gg[0][i];
    }
    for (int i = 0; i < 3; ++i) {
        FFT(ff[i], c, -1);
        for (int j = 0; j + 1 < n + m; ++j) {
            Add(h[j], mul(std::llround(ff[i][j].x) % mod, s[i]));
        }
    }
    FFT(gg[1], c, -1);
    for (int i = 0; i + 1 < n + m; ++i) {
        Add(h[i], mul(std::llround(gg[1][i].x) % mod, s[1]));
    }
    return h;
}
```

