# poly.h 文档

本文档是 [poly.h](https://github.com/FNatsuka/fstdlib/blob/master/source/poly.h) 的支持文档。您可以在此了解 poly.h 的使用方法。

## 基本介绍

poly.h 中定义了两个类，名为 `poly` 和 `m_poly`。它们都在命名空间 `fstdlib` 中。

其中，`poly` 是固定模数的多项式类，它的模数定义为 `fstdlib::mod`，默认值为 ![](http://latex.codecogs.com/gif.latex?998244353)。正常情况下，这个模数是一个常量。如果您需要修改它，您应当定义宏 `VARIABLE_MODULO`。您必须保证修改后：

- 模数是一个能够用于 NTT 的模数。换句话讲，它必须能表示为 ![](http://latex.codecogs.com/gif.latex?k\cdot%202^r+1) 的形式，且 ![](http://latex.codecogs.com/gif.latex?2^r) 足够大。
- 模数的两倍应当小于 32 位有符号整数的表示范围。

如果 ![](http://latex.codecogs.com/gif.latex?3) 不是您设定的模数的一个原根，您还应该将 `fstdlib::grt` 的值改为您设定模数的一个原根。

而 `m_poly` 是任意模数的多项式类。它的模数直接存储在实例中，您可以通过访问一个实例的 `mod` 成员来修改它。该种多项式的模数没有特别要求，但您仍应当保证：

- 模数的两倍应当小于 32 位有符号整数的表示范围。
- 任意两个进行运算的实例的模数相同。
- 如果模数不是质数，实例不能进行开根、求逆等运算。

`poly` 和 `m_poly` 的用法基本一致，但是构造方法不同。请您继续阅读以了解更多。

## 构造函数

|                方法                 |                             简介                             |
| :---------------------------------: | :----------------------------------------------------------: |
|        `poly(std::size_t n)`        | 构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0) 。 |
|     `poly(std::vector<int> a)`      | 用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个多项式。 |
|   `m_poly(std::size_t n, int p)`    | 构造一个长度为 ![](http://latex.codecogs.com/gif.latex?n) 的任意模数多项式，所有元素初始为 ![](http://latex.codecogs.com/gif.latex?0)。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p) 。 |
| `m_poly(std::vector<int> a, int p)` | 用 ![](http://latex.codecogs.com/gif.latex?a) 来初始化一个任意模数多项式。多项式的模数被初始化为 ![](http://latex.codecogs.com/gif.latex?p) 。 |

## 重载运算符和成员函数

|                     方法                     |              简介              |                      时间复杂度                       |
| :------------------------------------------: | :----------------------------: | :---------------------------------------------------: |
| `poly operator*(const poly &, const poly &)` |     计算两个多项式的卷积。     | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|   `poly &operator*=(poly &, const poly &)`   |     计算两个多项式的卷积。     | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|  `poly operator*(const poly &, const int &`  |   计算多项式和单项式的卷积。   |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator*=(poly &, const int &)`    |   计算多项式和单项式的卷积。   |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator*(const int &, const poly &)`  |   计算多项式和单项式的卷积。   |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator>>(const poly &, const int &)` |      将多项式右移指定次。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator>>=(poly &, const int &)`   |      将多项式右移指定次。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator<<(const poly &, const int &)` |      将多项式左移指定次。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator<<=(poly &, const int &)`   |      将多项式左移指定次。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator+(const poly &, const poly &)` |      计算两个多项式的和。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator+=(poly &, const poly &)`   |      计算两个多项式的和。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|  `poly operator+(const poly &, const int &`  |    计算多项式和单项式的和。    |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator+=(poly &, const int &)`    |    计算多项式和单项式的和。    |     ![](http://latex.codecogs.com/gif.latex?O(1))     |
| `poly operator+(const int &, const poly &)`  |    计算多项式和单项式的和。    |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator-(const poly &, const poly &)` |      计算两个多项式的差。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator-=(poly &, const poly &)`   |      计算两个多项式的差。      |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|  `poly operator-(const poly &, const int &`  |    计算多项式和单项式的差。    |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
|   `poly &operator-=(poly &, const int &)`    |    计算多项式和单项式的差。    |     ![](http://latex.codecogs.com/gif.latex?O(1))     |
| `poly operator-(const int &, const poly &)`  |    计算单项式和多项式的差。    |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator/(const poly &, const int &)`  | 计算多项式和单项式的逆的卷积， |     ![](http://latex.codecogs.com/gif.latex?O(n))     |
| `poly operator/=(const poly &, const int &)` | 计算多项式和单项式的逆的卷积， |     ![](http://latex.codecogs.com/gif.latex?O(n))     |

|                 方法                  |                          简介                          |                      时间复杂度                       |
| :-----------------------------------: | :----------------------------------------------------: | :---------------------------------------------------: |
|      `poly poly::inv(void)const`      |                计算多项式相同次数的逆。                | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
|  `poly poly::inv(std::size_t)const`   |                计算多项式指定次数的逆。                | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
| `poly poly::prefix(std::size_t)const` | 计算多项式前若干项的和。允许参数大于多项式本身的长度。 |     ![](http://latex.codecogs.com/gif.latex?O(n))     |

## 其他函数

|           方法            |          简介          |                      时间复杂度                       |
| :-----------------------: | :--------------------: | :---------------------------------------------------: |
| `poly sqrt(const poly &)` |  计算多项式的平方根。  | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
| `poly log(const poly &)`  | 计算多项式的自然对数。 | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |
| `poly exp(const poly &)`  | 计算多项式的指数函数。 | ![](http://latex.codecogs.com/gif.latex?O(n\log%20n)) |

目前尚未实现二次剩余，因此 `sqrt` 函数只有在多项式的常数项为 ![](http://latex.codecogs.com/gif.latex?1) 时才能正常工作。

由于本身的数学性质，`log` 函数的参数的常数项必须为 ![](http://latex.codecogs.com/gif.latex?1) ，`exp` 函数的参数的常数项必须为 ![](http://latex.codecogs.com/gif.latex?0) 。

## 计划

- 在卷积的两个多项式中的其中一个次数较小时，使用 ![](http://latex.codecogs.com/gif.latex?O(nm)) 的方法直接计算。
- 支持求二次剩余。
- 新增 `pow` 函数，计算多项式的指定次幂。
- 支持分治 NTT 实现的小常数 ![](http://latex.codecogs.com/gif.latex?O(n\log^2%20n)) 指数函数求法。



# 多项式汇总

来自 https://github.com/FNatsuka/fstdlib。

说明见 poly.h 文档

```cpp
/*
 * This file is part of the fstdlib project.
 * Version: Build v0.0.3
 * This is not a stable version. You can check for details and get the latest version at https://github.com/fei0319/fstdlib
 * If you have discovered any bugs, please report about it at https://github.com/fei0319/fstdlib/issues/new
 */

#ifndef _FEISTDLIB_POLY_
#define _FEISTDLIB_POLY_

#if __cplusplus >= 201103L
#define _FEISTDLIB_CPP11_
#endif

#include <cmath>
#include <cstdio>

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace fstdlib{

	typedef long long ll;
	
#ifndef VARIABLE_MODULO
	const int mod = 998244353, grt = 3;
#else
	int mod = 998244353, grt = 3;
#endif
	
	class poly{
	private:
		std::vector<int> data;
	public:
		poly(std::size_t len = std::size_t(0)){data = std::vector<int>(len); }
		poly(const std::vector<int> &b){data = b; }
		poly(const poly &b){data = b.data; }
		void resize(std::size_t len, int val = 0){data.resize(len, val); }
		std::size_t size(void)const{return data.size(); }
		void clear(void){data.clear(); }
#ifdef _FEISTDLIB_CPP11_
		void shrink_to_fit(void){data.shrink_to_fit(); }
#endif
		int &operator[](std::size_t b){return data[b]; }
		const int &operator[](std::size_t b)const{return data[b]; }
		
		poly prefix(std::size_t len)const;

		friend poly operator*(const poly &, const poly &);
		friend poly &operator*=(poly &, const poly &);
		
		friend poly operator+(const poly &, const poly &);
		friend poly &operator+=(poly &, const poly &);
		friend poly operator-(const poly &, const poly &);
		friend poly &operator-=(poly &, const poly &);
		
		friend poly operator*(const poly &, const int &);
		friend poly &operator*=(poly &, const int &);
		friend poly operator+(const poly &, const int &);
		friend poly &operator+=(poly &, const int &);
		friend poly operator-(const poly &, const int &);
		friend poly &operator-=(poly &, const int &);
		
		friend poly operator*(const int &, const poly &);
		friend poly operator+(const int &, const poly &);
		friend poly operator-(const int &, const poly &);
		
		poly inv(void)const;
		poly inv(std::size_t)const;
		
		friend poly operator/(const poly &, const int &);
		friend poly &operator/=(poly &, const int &);

		friend poly sqrt(const poly &);
		friend poly log(const poly &);
		friend poly exp(const poly &);
	};
	
	class arbitrary_modulo_poly{
	private:
		std::vector<int> data;
	public:
		int mod;
		arbitrary_modulo_poly(std::size_t len = std::size_t(0), int modulo = 1e9 + 7){mod = modulo, data = std::vector<int>(len); }
		arbitrary_modulo_poly(const std::vector<int> &b, int modulo = 1e9 + 7){mod = modulo, data = b; }
		void resize(std::size_t len, const int &val = 0){data.resize(len, val); }
		std::size_t size(void)const{return data.size(); }
		void clear(void){data.clear(); }
#ifdef _FEISTDLIB_CPP11_
		void shrink_to_fit(void){data.shrink_to_fit(); }
#endif
		int &operator[](std::size_t b){return data[b]; }
		const int &operator[](std::size_t b)const{return data[b]; }
		
		arbitrary_modulo_poly prefix(std::size_t len)const;

		friend arbitrary_modulo_poly operator*(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator*=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		
		friend arbitrary_modulo_poly operator+(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator+=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator-(const arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly &operator-=(arbitrary_modulo_poly &, const arbitrary_modulo_poly &);
		
		friend arbitrary_modulo_poly operator*(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator*=(arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly operator+(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator+=(arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly operator-(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator-=(arbitrary_modulo_poly &, const int &);
		
		friend arbitrary_modulo_poly operator*(const int &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator+(const int &, const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly operator-(const int &, const arbitrary_modulo_poly &);

		arbitrary_modulo_poly inv(void)const;
		arbitrary_modulo_poly inv(std::size_t)const;
		
		friend arbitrary_modulo_poly operator/(const arbitrary_modulo_poly &, const int &);
		friend arbitrary_modulo_poly &operator/=(arbitrary_modulo_poly &, const int &);

		friend arbitrary_modulo_poly sqrt(const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly log(const arbitrary_modulo_poly &);
		friend arbitrary_modulo_poly exp(const arbitrary_modulo_poly &);
	};
	
	typedef arbitrary_modulo_poly m_poly;
	
	namespace _FEISTDLIB_SECURITY_{
		const char
			*MODULO_DIF_ERROR = "The modulo of the two polynomial computed should be same.",
			*OUT_OF_CONVERGENCE_RADIUS = "The power series of logarithm/exponential of the polynomial does not converge.",
			*INVERSE_NOT_EXIST = "The inverse element of the polynomial/integer does not exist."; 
		
		int qpow(int a, int b, int p = mod){
			int res = 1;
			while(b){if(b & 1) res = (ll)res * a % p; a = (ll)a * a % p, b >>= 1; }
			return res;
		}
		
		inline int modulo_sqrt(int a, int p){
			return 1;
		}
		
		const long double PI = std::acos((long double)(-1)), EPS = 1e-18;
		
		template <typename FLOAT_T>
		FLOAT_T fabs(const FLOAT_T &x){
			return x > 0 ? x : -x;
		}
		
		template <typename FLOAT_T>
		FLOAT_T sin(const FLOAT_T &x, const long double &EPS = fstdlib::_FEISTDLIB_SECURITY_::EPS){
			FLOAT_T res = 0, delt = x;
			int d = 0;
			while(fabs(delt) > EPS){
				res += delt, ++d;
				delt *= - x * x / ((2 * d) * (2 * d + 1));
			}
			return res;
		}
		
		template <typename FLOAT_T>
		FLOAT_T cos(const FLOAT_T &x, const long double &EPS = fstdlib::_FEISTDLIB_SECURITY_::EPS){
			FLOAT_T res = 0, delt = 1;
			int d = 0;
			while(fabs(delt) > EPS){
				res += delt, ++d;
				delt *= - x * x / ((2 * d) * (2 * d - 1));
			}
			return res;
		}
		
		struct comp{
			long double x, y;
			comp(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}
			comp operator*(const comp &b)const{return comp(x * b.x - y * b.y, x * b.y + y * b.x); }
			comp operator+(const comp &b)const{return comp(x + b.x, y + b.y); }
			comp operator-(const comp &b)const{return comp(x - b.x, y - b.y); }
			comp conj(void){return comp(x, -y); }
		};
		
		std::vector<int> rev;
		void dft_for_modulo(std::vector<int>::iterator f, int n, int b){
			static std::vector<int> w;
			w.resize(n);
			for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(f[i], f[rev[i]]);
			for(int i = 2; i <= n; i <<= 1){
				w[0] = 1, w[1] = qpow(grt, (mod - 1) / i); if(b == -1) w[1] = qpow(w[1], mod - 2);
				for(int j = 2; j < i / 2; ++j) w[j] = (ll)w[j - 1] * w[1] % mod;
				for(int j = 0; j < n; j += i){
					std::vector<int>::iterator g = f + j, h = f + j + i / 2;
					for(int k = 0; k < i / 2; ++k){
						int p = g[k], q = (ll)h[k] * w[k] % mod;
						g[k] = (p + q) % mod, h[k] = (p - q) % mod;
					}
				}
			}
		}

		void dft_for_complex(std::vector<comp>::iterator f, int n, int b){
			static std::vector<comp> w;
			w.resize(n);
			for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(f[i], f[rev[i]]);
			for(int i = 2; i <= n; i <<= 1){
				w[0] = comp(1, 0), w[1] = comp(cos(2 * PI / i), b * sin(2 * PI / i));
				for(int j = 2; j < i / 2; ++j) w[j] = w[j - 1] * w[1];
				for(int j = 0; j < n; j += i){
					std::vector<comp>::iterator g = f + j, h = f + j + i / 2;
					for(int k = 0; k < i / 2; ++k){
						comp p = g[k], q = h[k] * w[k];
						g[k] = p + q, h[k] = p - q;
					}
				}
			}
		}
		
		inline int reduct(ll x, ll y, ll z, const int &mod){
			return (x % mod + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
	}
	
	poly poly::prefix(std::size_t len)const{
		std::vector<int> f(len);
		for(int i = std::min(len, size()); i >= 0; --i) f[i] = data[i];
		return f;
	}
	
	m_poly m_poly::prefix(std::size_t len)const{
		std::vector<int> f(len);
		for(int i = std::min(len, size()); i >= 0; --i) f[i] = data[i];
		return m_poly(f, mod);
	}
	
/*
 * Polynomial Convolution
 * Complexity: O(N log N)
 * Implementation: NTT(Number Theoretic Transform)
 * Verification: https://judge.yosupo.jp/problem/convolution_mod
 */
 
	poly operator*(const poly &_f, const poly &_h){
		using _FEISTDLIB_SECURITY_::rev;
		std::vector<int> f(_f.data), h(_h.data);
		
		int N = 1, sz = f.size() + h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_modulo(h.begin(), N, 1);
		
		for(int i = 0; i < N; ++i) f[i] = (ll)f[i] * h[i] % mod;
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), N, -1);
		int inv = _FEISTDLIB_SECURITY_::qpow(N, mod - 2);
		f.resize(sz);
		for(int i = 0; i < sz; ++i) f[i] = ((ll)f[i] * inv % mod + mod) % mod;
		
		return f;
	}
	
	poly &operator*=(poly &f, const poly &_h){		
		using _FEISTDLIB_SECURITY_::rev;
		std::vector<int> h(_h.data);
		
		int N = 1, sz = f.size() + h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.data.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_modulo(h.begin(), N, 1);
		
		for(int i = 0; i < N; ++i) f[i] = (ll)f[i] * h[i] % mod;
		_FEISTDLIB_SECURITY_::dft_for_modulo(f.data.begin(), N, -1);
		int inv = _FEISTDLIB_SECURITY_::qpow(N, mod - 2);
		f.resize(sz);
		for(int i = 0; i < sz; ++i) f[i] = ((ll)f[i] * inv % mod + mod) % mod;
		
		return f;
	}
	
/*
 * Arbitrary Module Polynomial Convolution
 * Complexity: O(N log N)
 * Implementation: MTT
 * Verification: https://www.luogu.com.cn/problem/P4245
 */ 
 
/*
 * This implementation is much faster than that based on NTT and Chinese Reminder Theorem. 
 * You can refer to it at
 *   https://yutong.site/wp-content/uploads/2018/09/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf .
 * Note that this implementation can perform correctly only when N is around or less than 1e5.
 */
 
	m_poly operator*(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		using _FEISTDLIB_SECURITY_::rev;
		using _FEISTDLIB_SECURITY_::comp;
		std::vector<comp> f, h;
		
		int N = 1, sz = _f.size() + _h.size() - 1;
		while(N < sz) N *= 2;
		f.resize(N), h.resize(N), rev.resize(N);
		
		for(int i = 0; i < (int)_f.size(); ++i) f[i].x = _f[i] & ((1 << 15) - 1), f[i].y = _f[i] >> 15;
		for(int i = 0; i < (int)_h.size(); ++i) h[i].x = _h[i] & ((1 << 15) - 1), h[i].y = _h[i] >> 15;
				
		for(int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
		_FEISTDLIB_SECURITY_::dft_for_complex(f.begin(), N, 1);
		_FEISTDLIB_SECURITY_::dft_for_complex(h.begin(), N, 1);
		
		std::vector<comp> p(N), q(N);
		for(int i = 0; i < N; ++i){
			p[i] = h[i] * (f[i] + f[(N - i) % N].conj()) * comp(0.50, 0);
			q[i] = h[i] * (f[i] - f[(N - i) % N].conj()) * comp(0, -0.5);
		}
		
		_FEISTDLIB_SECURITY_::dft_for_complex(p.begin(), N, -1);
		_FEISTDLIB_SECURITY_::dft_for_complex(q.begin(), N, -1);
		
		std::vector<int> r(sz);
		for(int i = 0; i < sz; ++i) r[i] = _FEISTDLIB_SECURITY_::reduct(p[i].x / N + 0.5, (p[i].y + q[i].x) / N + 0.5, q[i].y / N + 0.5, mod);
		
		return m_poly(r, mod);
	}
	
	m_poly &operator*=(m_poly &f, const m_poly &h){
		return f = f * h;
	}
	
/*
 * Polynomial Addition
 * Complexity: O(N)
 * Implementation: -
 * Verification: -
 */

	poly operator+(const poly &_f, const poly &_h){
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}
	
	poly &operator+=(poly &f, const poly &_h){
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}

	m_poly operator+(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator+=(m_poly &f, const m_poly &_h){
		if(f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = f.mod;
		
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] + _h[i]) % mod;
		return f;
	}

/*
 * Polynomial Subtraction
 * Complexity: O(N)
 * Implementation: -
 * Verification: -
 */

	poly operator-(const poly &_f, const poly &_h){
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}
	
	poly &operator-=(poly &f, const poly &_h){
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}

	m_poly operator-(const m_poly &_f, const m_poly &_h){
		if(_f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = _f.mod;
		
		std::vector<int> f(_f.data);
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator-=(m_poly &f, const m_poly &_h){
		if(f.mod != _h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::MODULO_DIF_ERROR);
		const int mod = f.mod;
		
		if(_h.size() > f.size()) f.resize(_h.size());
		for(int i = 0; i < (int)_h.size(); ++i) f[i] = (f[i] - _h[i]) % mod;
		return f;
	}

/*
 * Monomial Calculation
 * Complexity: -
 * Implementation: -
 * Verification: -
 */
		
	poly operator*(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}
		
	poly &operator*=(poly &f, const int &h){
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	poly operator+(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return f;
	}
		
	poly &operator+=(poly &f, const int &h){
		f[0] = (f[0] + h) % mod;
		return f;
	}

	poly operator-(const poly &_f, const int &h){
		std::vector<int> f(_f.data);
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	poly &operator-=(poly &f, const int &h){
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	poly operator*(const int &h, const poly &_f){
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	poly operator+(const int &h, const poly &_f){
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return f;
	}

	poly operator-(const int &h, const poly &_f){
		std::vector<int> f(_f.size());
		f[0] = (h - _f[0]) % mod;
		for(int i = 1; i < (int)f.size(); ++i) f[i] = -_f[i];
		return f;
	}
		
	m_poly operator*(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator*=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return f;
	}

	m_poly operator+(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator+=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		f[0] = (f[0] + h) % mod;
		return f;
	}

	m_poly operator-(const m_poly &_f, const int &h){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] - h) % mod;
		return m_poly(f, mod);
	}
		
	m_poly &operator-=(m_poly &f, const int &h){
		const int mod = f.mod;
	
		f[0] = (f[0] - h) % mod;
		return f;
	}
		
	m_poly operator*(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
		return m_poly(f, mod);
	}

	m_poly operator+(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (f[0] + h) % mod;
		return m_poly(f, mod);
	}
	
	m_poly operator-(const int &h, const m_poly &_f){
		const int mod = _f.mod;
	
		std::vector<int> f(_f.data);
		f[0] = (h - _f[0]) % mod;
		for(int i = 1; i < (int)f.size(); ++i) f[i] = -_f[i];
		return m_poly(f, mod);
	}
	
/*
 * Inverse of Polynomial
 * Complexity: O(N log N)
 * Verification: -
 */
	
	poly poly::inv(void)const{
		if(data[0] == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		using _FEISTDLIB_SECURITY_::rev;
		
		int N = 1, sz = size();
		while(N < sz) N *= 2;
		std::vector<int> f(N << 1), g(N << 1);
		f[0] = _FEISTDLIB_SECURITY_::qpow(data[0], mod - 2);
		
		for(int w = 2; w / 2 < sz; w <<= 1){
			for(int i = size(); i < w; ++i) g[i] = 0;
			for(int i = std::min(w, (int)size()) - 1; i >= 0; --i) g[i] = data[i];
			rev.resize(w * 2);
			for(int i = 0; i < w * 2; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? w : 0);
			
			_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), w << 1, 1);
			_FEISTDLIB_SECURITY_::dft_for_modulo(g.begin(), w << 1, 1);
			
			for(int i = 0; i < w * 2; ++i) f[i] = (ll)f[i] * (2 - (ll)f[i] * g[i] % mod) % mod;
			
			_FEISTDLIB_SECURITY_::dft_for_modulo(f.begin(), w << 1, -1);
			
			int inv = _FEISTDLIB_SECURITY_::qpow(w << 1, mod - 2);
			for(int i = 0; i < w; ++i) f[i] = (ll)f[i] * inv % mod;
			for(int i = w; i < w * 2; ++i) f[i] = 0;
		}
		f.resize(sz);
		
		return f;
	}
	
	poly poly::inv(std::size_t len)const{
		return prefix(len).inv();
	}
	
	m_poly m_poly::inv(void)const{
		if(data[0] == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		m_poly f(1, mod);
		f[0] = _FEISTDLIB_SECURITY_::qpow(this->data[0], mod - 2, mod);
		for(int w = 2; w / 2 < (int)size(); w <<= 1){
			f.resize(w);
			f *= (2 - f * prefix(w));
			f.resize(w);
		}
		f.resize(size());
		return f;
	}
	
	m_poly m_poly::inv(std::size_t len)const{
		return prefix(len).inv();
	}
	
/*
 * Division of Polynomial
 * Complexity: O(N + log P)
 * Verification: - 
 */

	poly operator/(const poly &_f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		std::vector<int> f(_f.data);
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, mod - 2);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
	poly &operator/=(poly &f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, mod - 2);
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
	m_poly operator/(const m_poly &_f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
		
		std::vector<int> f(_f.data);
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, _f.mod - 2), mod = _f.mod;
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return m_poly(f, mod);
	}
	
	m_poly &operator/=(m_poly &f, const int &h){
		if(h == 0)
			throw std::logic_error(_FEISTDLIB_SECURITY_::INVERSE_NOT_EXIST);
			
		const int inv = _FEISTDLIB_SECURITY_::qpow(h, f.mod - 2), mod = f.mod;
		for(int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
		return f;
	}
	
/*
 * Polynomial Square Root
 * Complexity: O(N log N)
 * Verification: - 
 */

	poly sqrt(const poly &h){
		poly f(1);
		f[0] = _FEISTDLIB_SECURITY_::modulo_sqrt(h.data[0], mod);
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			(f += h.prefix(w) * f.inv()) /= 2;
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
	
	m_poly sqrt(const m_poly &h){
		m_poly f(1, h.mod);
		f[0] = _FEISTDLIB_SECURITY_::modulo_sqrt(h.data[0], h.mod);
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			(f += h.prefix(w) * f.inv()) /= 2;
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}

/*
 * Polynomial Logarithm
 * Complexity: O(N log N)
 * Verification: -
 */
    
	poly log(const poly &h){
		if((h[0] - 1) % mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		
		poly d(h);
		for(int i = 1; i < (int)d.size(); ++i) d[i - 1] = (ll)d[i] * i % mod;
		d.resize(d.size() - 1);
		d *= h.inv();
		d.resize(h.size());
		for(int i = d.size() - 1; i >= 1; --i) d[i] = (ll)d[i - 1] * _FEISTDLIB_SECURITY_::qpow(i, mod - 2) % mod;
		d[0] = 0;
		return d;
	}
    
	m_poly log(const m_poly &h){
		if((h[0] - 1) % h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		const int mod = h.mod;
		
		m_poly d(h);
		for(int i = 1; i < (int)d.size(); ++i) d[i - 1] = (ll)d[i] * i % mod;
		d.resize(d.size() - 1);
		d *= h.inv();
		d.resize(h.size());
		for(int i = d.size() - 1; i >= 1; --i) d[i] = (ll)d[i - 1] * _FEISTDLIB_SECURITY_::qpow(i, mod - 2, mod) % mod;
		d[0] = 0;
		return d;
	}
	
/*
 * Polynomial Exponential
 * Complexity: O(N log N)
 * Verification: -
 */

	poly exp(const poly &h){
		if(h[0] % mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		
		poly f(1);
		f[0] = 1;
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			f *= (1 + h.prefix(w) - log(f));
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
	
	m_poly exp(const m_poly &h){
		if(h[0] % h.mod)
			throw std::logic_error(_FEISTDLIB_SECURITY_::OUT_OF_CONVERGENCE_RADIUS);
		const int mod = h.mod;
		
		m_poly f(1, mod);
		f[0] = 1;
		for(int w = 2; w / 2 < (int)h.size(); w <<= 1){
			f.resize(w);
			f *= (1 + h.prefix(w) - log(f));
			f.resize(w);
		}
		f.resize(h.size());
		return f;
	}
}

#endif
```

