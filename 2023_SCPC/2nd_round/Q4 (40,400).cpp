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
ost operator<<(ost out, pii &a) {
	out << a.first << " " << a.second;
	return out;
}

struct rode {
	ld x, h;
	ld area(rode &a) {
		return (h + a.h) * abs(x - a.x);
	}
};
using rodes = vector<rode>;

// 6 512mb 100,000
void test() {
	ld n;
	cin >> n;
	rodes r(n + 1);
	for (ld i = 1; i <= n; i++) {
		cin >> r[i].x >> r[i].h;
	}
	ld q;
	cin >> q;
	while (q--) {
		ld a, b;
		cin >> a >> b;
		ld m = r[a].area(r[b]);
		for (ld i = a; i <= b; i++) {
			for (ld j = i + 1; j <= b; j++) {
				m = min(m, r[i].area(r[j]));
			}
		}
		cout << m << endl;
	}
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