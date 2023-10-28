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

// 1.5 512mb 5,000
void test() {
	ld n, M, t;
	cin >> n;
	vec a(n);
	cin >> a >> M >> t;
	str bit(M, 1);
	bit.resize(n, 0);
	ld ans = 0;

	do {
		str sp = bit;
		for (ld _ = 0; _ < t; _++) {
			str tp = sp;
			for (ld i = 0; i < n; i++) {
				if (a[i] == 1) {
					if (i) {
						if (sp[i - 1]) tp[i] = 1;
					}
					if (i < n - 1) {
						if (sp[i + 1]) tp[i] = 1;
					}
				} else {
					if (i && i < n - 1) {
						if (sp[i - 1] && sp[i + 1]) {
							tp[i] = 1;
						}
					}
				}
			}
			sp = tp;
		}
		ans = max(ans, ld(count(all(sp), 1)));
	} while (prev_permutation(all(bit)));
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