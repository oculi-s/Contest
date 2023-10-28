#include <bits/stdc++.h>

using namespace std;
using ld = long long;
using str = string;
using vec = vector<ld>;
using snt = set<ld>;
using mat = vector<vec>;
using pii = pair<ld, ld>;
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
ist operator>>(ist in, pii &a) {
	in >> a.first >> a.second;
	return in;
}
ost operator<<(ost out, pii &a) {
	out << a.first << " " << a.second;
	return out;
}

// 4 512mb 8-20
void test() {
	ld n, k, m;
	cin >> n >> k >> m;
	vii edges(m);
	for (auto &x : edges) cin >> x;
	vec per(n);
	iota(all(per), 1);
	ld cnt = 0;
	do {
		cnt++;
		for (auto &[a, b] : edges) {
			if (per[a - 1] + per[b - 1] > k) {
				cnt--;
				break;
			};
		}
	} while (next_permutation(all(per)));
	cout << cnt << endl;
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