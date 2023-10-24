#include <bits/stdc++.h>

using ul = std::uint32_t;
using li = std::int32_t;
using ll = std::int64_t;
using ull = std::uint64_t;
using llf = long double;
using lf = double;
using vul = std::vector<ul>;
using vvul = std::vector<vul>;
using pulb = std::pair<ul, bool>;
using vpulb = std::vector<pulb>;
using vvpulb = std::vector<vpulb>;
using vb = std::vector<bool>;

const ul base = 998244353;

std::mt19937 rnd;

ul plus(ul a, ul b)
{
	return a + b < base ? a + b : a + b - base;
}

ul minus(ul a, ul b)
{
	return a < b ? a + base - b : a - b;
}

ul mul(ul a, ul b)
{
	return ull(a) * ull(b) % base;
}

void exgcd(li a, li b, li& x, li& y)
{
	if (b) {
		exgcd(b, a % b, y, x);
		y -= x * (a / b);
	} else {
		x = 1;
		y = 0;
	}
}

ul inverse(ul a)
{
	li x, y;
	exgcd(a, base, x, y);
	return x < 0 ? x + li(base) : x;
}

ul pow(ul a, ul b)
{
	ul ret = 1;
	ul temp = a;
	while (b) {
		if (b & 1) {
			ret = mul(ret, temp);
		}
		temp = mul(temp, temp);
		b >>= 1;
	}
	return ret;
}



ul sqrt(ul x)
{
	ul a;
	ul w2;
	while (true) {
		a = rnd() % base;
		w2 = minus(mul(a, a), x);
		if (pow(w2, base - 1 >> 1) == base - 1) {
			break;
		}
	}
	ul b = base + 1 >> 1;
	ul rs = 1, rt = 0;
	ul as = a, at = 1;
	ul qs, qt;
	while (b) {
		if (b & 1) {
			qs = plus(mul(rs, as), mul(mul(rt, at), w2));
			qt = plus(mul(rs, at), mul(rt, as));
			rs = qs;
			rt = qt;
		}
		b >>= 1;
		qs = plus(mul(as, as), mul(mul(at, at), w2));
		qt = plus(mul(as, at), mul(as, at));
		as = qs;
		at = qt;
	}
	return rs + rs < base ? rs : base - rs;
}

ul log(ul x, ul y, bool inited = false)
{
	static std::map<ul, ul> bs;
	const ul d = std::round(std::sqrt(lf(base - 1)));
	if (!inited) {
		bs.clear();
		for (ul i = 0, j = 1; i != d; ++i, j = mul(j, x)) {
			bs[j] = i;
		}
	}
	ul temp = inverse(pow(x, d));
	for (ul i = 0, j = 1; ; i += d, j = mul(j, temp)) {
		auto it = bs.find(mul(y, j));
		if (it != bs.end()) {
			return it->second + i;
		}
	}
}

ul powroot(ul x, ul y, bool inited = false)
{
	const ul g = 3;
	ul lgx = log(g, x, inited);
	li s, t;
	exgcd(y, base - 1, s, t);
	if (s < 0) {
		s += base - 1;
	}
	return pow(g, ull(s) * ull(lgx) % (base - 1));
}

class polynomial : public vul {
public:
	void clearzero() {
		while (size() && !back()) {
			pop_back();
		}
	}
	polynomial()=default;
	polynomial(const vul& a): vul(a) { }
	polynomial(vul&& a): vul(std::move(a)) { }
	ul degree() const {
		return size() - 1;
	}
	ul operator()(ul x) const {
		ul ret = 0;
		for (ul i = size() - 1; ~i; --i) {
			ret = mul(ret, x);
			ret = plus(ret, vul::operator[](i));
		}
		return ret;
	}
};

polynomial& operator+=(polynomial& a, const polynomial& b)
{
	a.resize(std::max(a.size(), b.size()), 0);
	for (ul i = 0; i != b.size(); ++i) {
		a[i] = plus(a[i], b[i]);
	}
	a.clearzero();
	return a;
}

polynomial operator+(const polynomial& a, const polynomial& b)
{
	polynomial ret = a;
	return ret += b;
}

polynomial& operator-=(polynomial& a, const polynomial& b)
{
	a.resize(std::max(a.size(), b.size()), 0);
	for (ul i = 0; i != b.size(); ++i) {
		a[i] = minus(a[i], b[i]);
	}
	a.clearzero();
	return a;
}

polynomial operator-(const polynomial& a, const polynomial& b)
{
	polynomial ret = a;
	return ret -= b;
}

class ntt_t {
public:
	static const ul lgsz = 20;
	static const ul sz = 1 << lgsz;
	static const ul g = 3;
	ul w[sz + 1];
	ul leninv[lgsz + 1];
	ntt_t() {
		ul wn = pow(g, (base - 1) >> lgsz);
		w[0] = 1;
		for (ul i = 1; i <= sz; ++i) {
			w[i] = mul(w[i - 1], wn);
		}
		leninv[lgsz] = inverse(sz);
		for (ul i = lgsz - 1; ~i; --i) {
			leninv[i] = plus(leninv[i + 1], leninv[i + 1]);
		}
	}
	void operator()(vul& v, ul& n, bool inv) {
		ul lgn = 0;
		while ((1 << lgn) < n) {
			++lgn;
		}
		n = 1 << lgn;
		v.resize(n, 0);
		for (ul i = 0, j = 0; i != n; ++i) {
			if (i < j) {
				std::swap(v[i], v[j]);
			}
			ul k = n >> 1;
			while (k & j) {
				j &= ~k;
				k >>= 1;
			}
			j |= k;
		}
		for (ul lgmid = 0; (1 << lgmid) != n; ++lgmid) {
			ul mid = 1 << lgmid;
			ul len = mid << 1;
			for (ul i = 0; i != n; i += len) {
				for (ul j = 0; j != mid; ++j) {
					ul t0 = v[i + j];
					ul t1 = mul(w[inv ? (len - j << lgsz - lgmid - 1) : (j << lgsz - lgmid - 1)], v[i + j + mid]);
					v[i + j] = plus(t0, t1);
					v[i + j + mid] = minus(t0, t1);
				}
			}
		}
		if (inv) {
			for (ul i = 0; i != n; ++i) {
				v[i] = mul(v[i], leninv[lgn]);
			}
		}
	}
} ntt;

polynomial& operator*=(polynomial& a, const polynomial& b)
{
	if (!b.size() || !a.size()) {
		a.resize(0);
		return a;
	}
	polynomial temp = b;
	ul npmp1 = a.size() + b.size() - 1;
	if (ull(a.size()) * ull(b.size()) <= ull(npmp1) * ull(50)) {
		temp.resize(0);
		temp.resize(npmp1, 0);
		for (ul i = 0; i != a.size(); ++i) {
			for (ul j = 0; j != b.size(); ++j) {
				temp[i + j] = plus(temp[i + j], mul(a[i], b[j]));
			}
		}
		a = temp;
		a.clearzero();
		return a;
	}
	ntt(a, npmp1, false);
	ntt(temp, npmp1, false);
	for (ul i = 0; i != npmp1; ++i) {
		a[i] = mul(a[i], temp[i]);
	}
	ntt(a, npmp1, true);
	a.clearzero();
	return a;
}

polynomial operator*(const polynomial& a, const polynomial& b)
{
	polynomial ret = a;
	return ret *= b;
}

polynomial& operator*=(polynomial& a, ul b)
{
	if (!b) {
		a.resize(0);
		return a;
	}
	for (ul i = 0; i != a.size(); ++i) {
		a[i] = mul(a[i], b);
	}
	return a;
}

polynomial operator*(const polynomial& a, ul b)
{
	polynomial ret = a;
	return ret *= b;
}

polynomial inverse(const polynomial& a, ul lgdeg)
{
	polynomial ret({inverse(a[0])});
	polynomial temp;
	polynomial tempa;
	for (ul i = 0; i != lgdeg; ++i) {
		tempa.resize(0);
		tempa.resize(1 << i << 1, 0);
		for (ul j = 0; j != tempa.size() && j != a.size(); ++j) {
			tempa[j] = a[j];
		}
		temp = ret * (polynomial({2}) - tempa * ret);
		if (temp.size() > (1 << i << 1)) {
			temp.resize(1 << i << 1, 0);
		}
		temp.clearzero();
		std::swap(temp, ret);
	}
	return ret;
}

void quotientremain(const polynomial& a, polynomial b, polynomial& q, polynomial& r)
{
	if (a.size() < b.size()) {
		q = polynomial();
		r = std::move(a);
		return;
	}
	std::reverse(b.begin(), b.end());
	auto ta = a;
	std::reverse(ta.begin(), ta.end());
	ul n = a.size() - 1;
	ul m = b.size() - 1;
	ta.resize(n - m + 1);
	ul lgnmmp1 = 0;
	while ((1 << lgnmmp1) < n - m + 1) {
		++lgnmmp1;
	}
	q = ta * inverse(b, lgnmmp1);
	q.resize(n - m + 1);
	std::reverse(b.begin(), b.end());
	std::reverse(q.begin(), q.end());
	r = a - b * q;
}

polynomial mod(const polynomial& a, const polynomial& b)
{
	polynomial q, r;
	quotientremain(a, b, q, r);
	return r;
}

polynomial quotient(const polynomial& a, const polynomial& b)
{
	polynomial q, r;
	quotientremain(a, b, q, r);
	return q;
}

polynomial sqrt(const polynomial& a, ul lgdeg)
{
	polynomial ret({sqrt(a[0])});
	polynomial temp;
	polynomial tempa;
	for (ul i = 0; i != lgdeg; ++i) {
		tempa.resize(0);
		tempa.resize(1 << i << 1, 0);
		for (ul j = 0; j != tempa.size() && j != a.size(); ++j) {
			tempa[j] = a[j];
		}
		temp = (tempa * inverse(ret, i + 1) + ret) * (base + 1 >> 1);
		if (temp.size() > (1 << i << 1)) {
			temp.resize(1 << i << 1, 0);
		}
		temp.clearzero();
		std::swap(temp, ret);
	}
	return ret;
}

polynomial diffrential(const polynomial& a)
{
    if (!a.size()) {
        return a;
    }
    polynomial ret(vul(a.size() - 1, 0));
    for (ul i = 1; i != a.size(); ++i) {
        ret[i - 1] = mul(a[i], i);
    }
    return ret;
}

polynomial integral(const polynomial& a)
{
    polynomial ret(vul(a.size() + 1, 0));
    for (ul i = 0; i != a.size(); ++i) {
        ret[i + 1] = mul(a[i], inverse(i + 1));
    }
    return ret;
}

polynomial ln(const polynomial& a, ul lgdeg)
{
    polynomial da = diffrential(a);
    polynomial inva = inverse(a, lgdeg);
    polynomial ret = integral(da * inva);
    if (ret.size() > (1 << lgdeg)) {
        ret.resize(1 << lgdeg);
        ret.clearzero();
    }
    return ret;
}

polynomial exp(const polynomial& a, ul lgdeg)
{
    polynomial ret({1});
    polynomial temp;
    polynomial tempa;
    for (ul i = 0; i != lgdeg; ++i) {
        tempa.resize(0);
        tempa.resize(1 << i << 1, 0);
        for (ul j = 0; j != tempa.size() && j != a.size(); ++j) {
            tempa[j] = a[j];
        }
        temp = ret * (polynomial({1}) - ln(ret, i + 1) + tempa);
        if (temp.size() > (1 << i << 1)) {
            temp.resize(1 << i << 1, 0);
        }
        temp.clearzero();
        std::swap(temp, ret);
    }
    return ret;
}

polynomial pow(const polynomial& a, ul k, ul lgdeg)
{
	return exp(ln(a, lgdeg) * k, lgdeg);
}

polynomial alpi[1 << 16][17];

polynomial getalpi(const ul x[], ul l, ul lgrml)
{
	if (lgrml == 0) {
		return alpi[l][lgrml] = vul({minus(0, x[l]), 1});
	}
	return alpi[l][lgrml] = getalpi(x, l, lgrml - 1) * getalpi(x, l + (1 << lgrml - 1), lgrml - 1);
}

void multians(const polynomial& f, const ul x[], ul y[], ul l, ul lgrml)
{
	if (f.size() <= 700) {
		for (ul i = l; i != l + (1 << lgrml); ++i) {
			y[i] = f(x[i]);
		}
		return;
	}
	if (lgrml == 0) {
		y[l] = f(x[l]);
		return;
	}
	multians(mod(f, alpi[l][lgrml - 1]), x, y, l, lgrml - 1);
	multians(mod(f, alpi[l + (1 << lgrml - 1)][lgrml - 1]), x, y, l + (1 << lgrml - 1), lgrml - 1);
}

ul sqrt(ul x)
{
	ul a;
	ul w2;
	while (true) {
		a = rnd() % base;
		w2 = minus(mul(a, a), x);
		if (pow(w2, base - 1 >> 1) == base - 1) {
			break;
		}
	}
	ul b = base + 1 >> 1;
	ul rs = 1, rt = 0;
	ul as = a, at = 1;
	ul qs, qt;
	while (b) {
		if (b & 1) {
			qs = plus(mul(rs, as), mul(mul(rt, at), w2));
			qt = plus(mul(rs, at), mul(rt, as));
			rs = qs;
			rt = qt;
		}
		b >>= 1;
		qs = plus(mul(as, as), mul(mul(at, at), w2));
		qt = plus(mul(as, at), mul(as, at));
		as = qs;
		at = qt;
	}
	return rs + rs < base ? rs : base - rs;
}

ul log(ul x, ul y, bool inited = false)
{
	static std::map<ul, ul> bs;
	const ul d = std::round(std::sqrt(lf(base - 1)));
	if (!inited) {
		bs.clear();
		for (ul i = 0, j = 1; i != d; ++i, j = mul(j, x)) {
			bs[j] = i;
		}
	}
	ul temp = inverse(pow(x, d));
	for (ul i = 0, j = 1; ; i += d, j = mul(j, temp)) {
		auto it = bs.find(mul(y, j));
		if (it != bs.end()) {
			return it->second + i;
		}
	}
}

ul powroot(ul x, ul y, bool inited = false)
{
	const ul g = 3;
	ul lgx = log(g, x, inited);
	li s, t;
	exgcd(y, base - 1, s, t);
	if (s < 0) {
		s += base - 1;
	}
	return pow(g, ull(s) * ull(lgx) % (base - 1));
}

ul n;

int main()
{
	std::scanf("%u", &n);
	polynomial f;
	for (ul i = 0; i <= n; ++i) {
		ul t;
		std::scanf("%u", &t);
		f.push_back(t % base);
	}
	polynomial g = exp(ln(f * inverse(f[0]), 17) * inverse(3), 17) * powroot(f[0], 3);
	while (g.size() <= n) {
		g.push_back(0);
	}
	for (ul i = 0; i <= n; ++i) {
		if (i) {
			std::putchar(' ');
		}
		std::printf("%u", g[i]);
	}
	std::putchar('\n');
    return 0;
}