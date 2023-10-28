#include <stdio.h>
#include <stdlib.h>
#define M 300000

typedef long long lld;
lld t, ti, n, i, j, p[M], v[M], k, c, a[M], b[M], ans;

int main(void) {
	setbuf(stdout, NULL);
	scanf("%lld", &t);
	for (ti = 1; ti <= t; ti++) {
		ans = 0;
		scanf("%lld", &n);
		for (i = 0; i < n; i++)
			scanf("%lld", p + i);
		for (i = 0; i < n; i++)
			scanf("%lld", v + i);
		for (i = 0; i < n; i++) {
			a[i] = 0, b[i] = 0;
			for (j = i - 1; j >= 0; j--)
				if (v[i] == v[j]) {
					b[i] = b[j] + 1;
					a[i] = a[j];
					break;
				}
			if (!a[i])
				for (j = 0; j < n; j++)
					if (v[j] < v[i])
						a[i]++;
			ans += llabs(p[i] - p[a[i] + b[i]]);
		}
		printf("Case #%lld\n%lld\n", ti, ans);
	}
	return 0;
}