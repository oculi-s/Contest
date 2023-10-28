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

// 1s 512mb 1,000,000
void test() {
	ld n, d;
	cin >> n >> d;
	map<ld, ld> mem;
	for (int i = 0; i < n; i++) {
		ld x;
		cin >> x;
		mem[x]++;
	}
	vec dist, cnt;
	for (auto x : mem) {
		dist.pb(x.first);
		cnt.pb(x.second);
	}
	int m = dist.sz();
	vec sum = cnt;
	for (int i = 1; i < m; i++) {
		if (dist[i - 1] >= 0) {
			sum[i] += sum[i - 1];
		}
	}
	for (int i = m - 2; i >= 0; i--) {
		if (dist[i + 1] <= 0) {
			sum[i] += sum[i + 1];
		}
	}
	ld ans = 0;
	for (int i = 0; i < m; i++) {
		ld di = abs(dist[i]);
		if (di <= d) {
			ans = max(ans, sum[i]);
		}
		if (di * 2 < d && di) {
			ld left = d - di * 2;
			ld j;
			if (dist[i] > 0) {
				j = LOW(dist, -left);
			} else {
				j = LOW(dist, left);
			}
			if (j == m) j--;
			if (dist[j] > left) j--;
			if (dist[i] * dist[j] > 0) continue;
			ans = max(ans, sum[i] + sum[j] - mem[0]);
		}
	}
	cout << ans << endl;
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