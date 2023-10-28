#include <bits/stdc++.h>

using namespace std;
using ld = long long;
using str = string;
using vec = vector<ld>;
using snt = set<ld>;
using mat = vector<vec>;
using mat3d = vector<mat>;
using pii = pair<ld, ld>;
using vii = vector<pii>;
using mii = vector<vii>;
using mii3d = vector<mii>;
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

mii3d nxt(7, mii(6, vii(6, {-1, -1})));

// 512mb 100,000
void test() {
	ld n, k;
	cin >> n >> k;
	vec a(n);
	cin >> a;
	// cnts번 돌고 다음번엔 last에서 시작
	vec last(n, 0);
	vec cnts(n, 0);
	vec anss(n, 1);
	for (ld i = 0; i < n; i++) {
		pii cur = {1, 0};
		ld j = i;
		while (cur.first != -1 || cur.second != -1) {
			cur = nxt[cur.first][cur.second][a[j] - 1];
			j++;
			if (j == n) {
				j = 0;
				cnts[i]++;
			}
		}
		last[i] = j;
	}
	// cnts가 0인걸 보정
	vec cnts2 = cnts, last2 = last;
	for (ld i = n - 1; i >= 0; i--) {
		if (cnts[i]) continue;
		auto nx = last2[i];
		cnts2[i] = cnts2[nx];
		anss[i] += anss[nx];
		last2[i] = last2[nx];
	}

	ld ans = 0, pos = 0, cnt = 0;
	while (cnt < k) {
		if (cnt + cnts2[pos] < k) {
			cnt += cnts2[pos];
			ans += anss[pos];
			pos = last2[pos];
		} else if (cnt + cnts2[pos] >= k) {
			cnt += cnts[pos];
			pos = last[pos];
			if (cnt < k || cnt == k && !pos) {
				ans++;
			}
		}
	}
	cout << ans << endl;
}

int main() {
	nxt[1] = {
		{{1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 0}},
		{{1, 2}, {1, 3}, {1, 4}, {2, 0}, {3, 1}},
		{{1, 3}, {1, 4}, {2, 0}, {3, 1}, {3, 2}},
		{{1, 4}, {2, 0}, {3, 1}, {3, 2}, {3, 3}},
		{{2, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}}};
	nxt[2] = {
		{{2, 1}, {2, 2}, {4, 3}, {2, 3}, {2, 4}},
		{{2, 2}, {4, 3}, {2, 3}, {2, 4}, {6, 0}},
		{{4, 3}, {2, 3}, {2, 4}, {6, 0}, {6, 1}},
		{{2, 4}, {6, 0}, {6, 1}, {6, 2}, {6, 3}},
		{{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}}};
	nxt[3] = {
		{},
		{{3, 2}, {3, 3}, {3, 4}, {4, 0}, {5, 1}},
		{{3, 3}, {3, 4}, {4, 0}, {5, 1}, {5, 2}},
		{{3, 4}, {4, 0}, {5, 1}, {5, 2}, {5, 3}},
		{{4, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}}};
	nxt[4] = {
		{{4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}},
		{{4, 2}, {4, 3}, {4, 4}, {4, 5}, {0, 0}},
		{{4, 3}, {4, 4}, {4, 5}, {0, 0}, {-1, -1}},
		{{4, 4}, {4, 5}, {0, 0}, {-1, -1}, {-1, -1}},
		{{4, 5}, {0, 0}, {-1, -1}, {-1, -1}, {-1, -1}},
		{{0, 0}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}};
	nxt[5] = {
		{},
		{{5, 2}, {5, 3}, {5, 4}, {6, 0}, {6, 1}},
		{{5, 3}, {5, 4}, {6, 0}, {6, 1}, {6, 2}},
		{{5, 4}, {6, 0}, {6, 1}, {6, 2}, {6, 3}},
		{{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}}};
	nxt[6] = {
		{{6, 1}, {6, 2}, {6, 3}, {6, 4}, {0, 0}},
		{{6, 2}, {6, 3}, {6, 4}, {0, 0}, {-1, -1}},
		{{6, 3}, {6, 4}, {0, 0}, {-1, -1}, {-1, -1}},
		{{6, 4}, {0, 0}, {-1, -1}, {-1, -1}, {-1, -1}},
		{{0, 0}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}};
	nxt[0][0] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
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