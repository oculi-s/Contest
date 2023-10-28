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

bool balanced(str s) {
	ld d = 0;
	for (auto &x : s) {
		d += x == '(' ? 1 : -1;
		if (d < 0) return 0;
	}
	return d == 0;
}

ld raw(str &s) {
	ld n = s.sz();
	ld cnt = 0;
	for (ld i = 0; i < n; i++) {
		ld d1 = 0, d2 = 0;
		for (ld j = i; j < n; j++) {
			if (s[j] == '(') {
				if (d2 < 0) break;
				d1++;
			}
			if (s[j] == ')') {
				if (d2 > 0) break;
				d1--;
			}
			if (s[j] == '{') {
				if (d1 < 0) break;
				d2++;
			}
			if (s[j] == '}') {
				if (d1 > 0) break;
				d2--;
			}
			if (!d1 && !d2) cnt++;
		}
	}
	return cnt;
}

void rec(str &s, ld l, ld r, ld n, ld &cnt, vec &mass, vec &lend) {
	if (l < 0 || r >= n) return;
	if (mass[r]) return;
	if ((s[l] != '(' || s[r] != ')') && (s[l] != '{' || s[r] != '}')) {
		mass[r] = -1;
		rec(s, r, r + 1, n, cnt, mass, lend);
		return;
	}
	lend[r] = l;
	mass[r] = 1;
	ld right = 0, left = 0;
	// 왼쪽 sibling
	if (l) {
		left = mass[l - 1];
		left = left < 0 ? 0 : left;
		if (lend[l - 1]) {
			l = lend[l - 1];
			lend[r] = l;
		}
	}
	// 오른쪽 sibling
	while (r + 2 < n && (s[r + 1] == '(' && s[r + 2] == ')' || s[r + 1] == '{' && s[r + 2] == '}')) {
		r += 2, right++, mass[r] = -1, lend[r] = l;
	}
	ld m = left + right + 1;
	mass[r] = m;
	cnt += (m * (m + 1)) / 2 - (left * (left + 1)) / 2;
	rec(s, l - 1, r + 1, n, cnt, mass, lend);
	rec(s, r, r + 1, n, cnt, mass, lend);
}

ld get(str &s) {
	ld n = s.sz(), cnt = 0;
	vec mass(n, 0), lend(n, 0);
	rec(s, 0, 1, n, cnt, mass, lend);
	return cnt;
}

// 1.5 512mb 1,000,000
void test() {
	ld n;
	str s;
	cin >> n >> s;
	cout << get(s) << endl;
	return;

	// ld v1 = 1, v2 = 1;
	// str key = "{}()";
	// while (v1 == v2) {
	// 	ld n = rand() % 100 + 1;
	// 	str s;
	// 	for (ld i = 0; i < n; i++) {
	// 		s.pb(key[rand() % 4]);
	// 	}
	// 	v1 = get(s);
	// 	v2 = raw(s);
	// 	if (v1 != v2) {
	// 		cout << s << endl;
	// 		cout << v1 << " " << v2 << endl;
	// 	}
	// }
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