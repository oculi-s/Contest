#include <bits/stdc++.h>

using namespace std;
using ld = long long;
using str = string;
using vec = vector<ld>;
using snt = set<int>;
using mat = vector<vec>;
using pii = pair<int, int>;
using vii = vector<pii>;
#define all(a)	  a.begin(), a.end()
#define rev		  reverse
#define pb		  push_back
#define sz		  size
#define ist		  istream &
#define ost		  ostream &
#define LOW(a, b) lower_bound(all(a), b) - a.begin()
#define UPP(a, b) upper_bound(all(a), b) - a.begin()

ist operator>>(ist in, vec &a) {
	for (auto &x : a) in >> x;
	return in;
}
ost operator<<(ost out, vec &a) {
	for (auto &x : a) out << x << " ";
	return out;
}

const ld D = 1e9 + 7;
ld pp(ld n, ld k) {
	ld v = 1;
	while (k) {
		if (k & 1) v *= n, v %= D;
		n *= n, n %= D, k >>= 1;
	}
	return v;
}

ld comb(ld n, ld k) {
	ld r = 1;
	for (ld d = 1; d <= k; d++) {
		r *= n--;
		r %= D;
		r *= pp(d, D - 2);
		r %= D;
	}
	return r;
}

bool check(vec &a) {
	for (auto &x : a)
		if (x > 1) return 1;
	return 0;
}

ld KMP(vec &s) {
	ld n = s.sz();
	vec next(n, 0);
	for (int i = 1; i < n; i++) {
		ld k = next[i - 1];
		while (1) {
			if (s[i] == s[k]) {
				next[i] = k + 1;
				break;
			} else if (k == 0) {
				next[i] = 0;
				break;
			} else {
				k = next[k - 1];
			}
		}
	}
	ld L = n - next[n - 1];
	if (n % L) return n;
	return L;
}

vec x;
ld find(ld a) {
	if (x[a] == a) return a;
	return x[a] = find(x[a]);
}

void unio(ld a, ld b) {
	x[find(b)] = find(a);
}

struct group {
	ld l = 2e9, r = -1, life = 0;
	vec ch;
};

// 1s 512mb 500,000
void test() {
	ld n;
	cin >> n;
	vec a(n, 0);
	cin >> a;
	ld s = 0;
	for (auto &x : a) s += x;
	if (s >= n) {
		cout << 1 << endl;
		return;
	} else if (!check(a)) {
		cout << KMP(a) << endl;
		return;
	}
	vii nz;
	for (int i = 0; i < n; i++) {
		if (a[i]) {
			nz.pb({i, a[i]});
		}
	}

	ld m = nz.sz(), cnt = 0;
	x.resize(m);
	iota(all(x), 0);
	vector<group> g(m);
	for (int i = 0; i < m; i++) {
		ld j = nz[i].first;
		g[i].l = g[i].r = j;
	}
	vec idx(m);
	iota(all(idx), 0);
	for (int i = 0; i < n; i++) {
		vec tidx;
		ld m = idx.sz();
		for (int ii = 0; ii < m; ii++) {
			ld j = idx[ii];
			ld k = idx[(ii + 1) % m];
			if (x[j] == x[k]) {
				continue;
			}
			auto &gx = g[x[j]];
			auto &gy = g[x[k]];
			if ((gx.r + 1) % n == gy.l) {
				gy.l = gx.l;
				gx.r = gy.r;
				unio(j, k);
				continue;
			}
			a[gx.l]--;
			gx.r = (gx.r + 1) % n;
			a[gx.r]++;
			while (!a[gx.l]) {
				gx.l = (gx.l + 1) % n;
			}
			ld l = idx[(ii - 1 + m) % m];
			auto &gz = g[x[l]];
			if ((gz.r + 1) % n == gx.l) {
				gx.l = gz.l;
				gz.r = gx.r;
				unio(j, l);
				continue;
			}
			tidx.pb(x[j]);
		}
		if (!tidx.sz()) break;
		idx = tidx;
	}
	cout << KMP(a) << endl;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << endl;
		test();
	}
	return 0;
}