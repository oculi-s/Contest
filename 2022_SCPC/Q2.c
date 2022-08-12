#include <stdio.h>
#define M 500001
#define D 1000000007

typedef long long lld;
lld t, ti, n, k, i, ans, s[M], x[M];

void dfs(lld start, lld end, lld cnt) {
	if (cnt == 0) ans = (ans + 1) % D;
	else if (cnt <= n - end) {
		if ((s[end] - s[start]) * k == s[n])
			dfs(end, end + 1, cnt - 1);
		dfs(start, end + 1, cnt);
	}
}

int main() {
	setbuf(stdout, NULL);
	scanf("%lld", &t);
	for (ti = 1; ti <= t; ti++) {
		ans = 0;
		scanf("%lld %lld", &n, &k);
		for (i = 1; i <= n; i++) {
			scanf("%lld", x + i);
			s[i] = x[i] + s[i - 1];
		}
		dfs(0, 1, k - 1);
		printf("Case #%lld\n%lld\n", ti, ans % D);
	}
}
