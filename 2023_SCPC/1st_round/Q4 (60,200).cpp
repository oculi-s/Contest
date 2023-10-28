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

void rec(vec &dp, ld i, str s, str &p, str &r) {
	if (i >= r.sz()) return;
	ld n = s.sz();
	if (p.rfind(s, 0) == 0) {
		dp[i + 1] = min(dp[i + 1], dp[i + 1 - n] + 1);
	}
	rec(dp, i + 1, s + r[i + 1], p, r);
}

// 1s 512mb 350,000
void test() {
	str r, p;
	cin >> r >> p;
	ld n = r.sz();
	if (n > 400) {
		cout << -1 << endl;
		return;
	}
	vec dp(n + 1, 2e9);
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		rec(dp, i, str(1, r[i]), p, r);
	}
	ld ans = (dp[n] > n ? -1 : dp[n]);
	cout << ans << endl;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << endl;
		test();
	}
	return 0;
}