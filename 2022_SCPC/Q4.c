#include <stdio.h>
#define M 1000002

int sx, sy, ex, ey, n, m, i, go, t, ti, x[M], y[M];
char s[M];

void dfs(int x[M], int sx, int ex) {
	if (go)
		if (ey - sy == ex - sx) {
			int i;
			for (i = sx; i <= ex; i++)
				if (x[i] != y[i])
					break;
			if (i == ex + 1)
				go = 0;
		}
		else if (ey - sy < ex - sx) {
			int tsx = x[sx], tex = x[ex];
			if (x[sx] > y[sx])
				x[sx] = y[sx], dfs(x, sx, ex), x[sx] = tsx;
			else
				x[sx + 1] += tsx, dfs(x, sx + 1, ex), x[sx + 1] -= tsx;

			if (x[ex] > y[ex])
				x[ex] = y[ex], dfs(x, sx, ex), x[ex] = tex;
			else
				x[ex - 1] += tex, dfs(x, sx, ex - 1), x[ex - 1] -= tex;
		}
}

int main() {
	setbuf(stdout, NULL);
	scanf("%d", &t);
	for (ti = 1; ti <= t; ti++) {
		sx = 1, sy = 1, ex = 1, ey = 1, go = 1;
		scanf("%d %d", &n, &m);
		scanf("%s", s);
		for (i = 0; i < n; i++)
			x[i] = 0, y[i] = 0;
		for (i = 0; i < n; i++)
			if (s[i] == 'a')
				x[ex]++;
			else
				ex++;
		scanf("%s", s);
		for (i = 0; i < m; i++)
			if (s[i] == 'a')
				y[ey]++;
			else
				ey++;
		dfs(x, sx, ex);
		printf("Case #%d\n%s\n", ti, go ? "NO" : "YES");
	}
}
