# BSGS & exBSGS

求解满足 $a ^ x \equiv b \bmod p$ 的 $x$

```cpp
LL BSGS(LL a, LL b, LL p){
	if(1 % p == b % p) return 0;
	LL k = sqrt(p) + 1;
	unordered_map<LL, LL> hash;
	for(LL i = 0, j = b % p; i < k; i++){
		hash[j] = i;
		j = j * a % p;
	}
	LL ak = 1;
	for(int i = 1; i <= k; i++) ak = ak * a % p;
	for(int i = 1, j = ak; i <= k; i++){
		if(hash.count(j)) return (LL)i * k - hash[j];
		j = (LL)j * ak % p;
	}
	return -inf;
}
```

$(a, p) \neq 1$ 的情形

```cpp
void exgcd(LL a, LL b, LL &x0, LL &y0, LL &d){}

LL BSGS(LL a, LL b, LL p){}

LL exBSGS(LL a, LL b, LL p){
	b = (b % p + p) % p;
	if((LL)1 % p == b % p) return 0;
	LL x, y, d;
	exgcd(a, p, x, y, d);
	if(d > 1){
		if(b % d != 0) return -inf;
		LL d1;
		exgcd(a / d, p / d, x, y, d1);
		return exBSGS(a, b / d * x % (p / d), p / d) + 1;
	}
	return BSGS(a, b, p);
}
```

