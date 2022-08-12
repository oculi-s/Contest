#include <stdio.h>
#define M 2001

typedef long long lld;
lld t, ti, n, i, j, ans, b[M][M];
char s[M + 1];

void setA() {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			b[i][j] = (n - 1 - i) * j + (n - 1 - j) * i;
}

void setB(int y, int x) {
	b[y][x] = -1;
	int i, j;
	for (i = y + 1; i < n; i++)
		for (j = 0; j < x; j++)
			b[i][j]--;
	for (i = 0; i < y; i++)
		for (j = x + 1; j < n; j++)
			b[i][j]--;
}

void setC(int y, int x) {
	int i, j;
	for (i = 0; i <= y; i++)
		for (j = 0; j <= x; j++)
			if (b[i][j] > 0)
				if (!find(y, x, i, j))
					b[y][x]++;
	for (i = y; i < n; i++)
		for (j = x; j < n; j++)
			if (b[i][j] > 0)
				if (!find(i, j, y, x))
					b[y][x]++;
}

int find(int y, int x, int y1, int x1) {
	if (y1 == y && x1 == x)
		return 1;
	else if (b[y1][x1] < 0)
		return 0;
	else if (y1 == y && x1 < x)
		return find(y, x, y1, x1 + 1);
	else if (x1 == x && y1 < y)
		return find(y, x, y1 + 1, x1);
	else if (y1 < y && x1 < x)
		return find(y, x, y1 + 1, x1) || find(y, x, y1, x1 + 1);
	else
		return 0;
}

int main(void) {
	setbuf(stdout, NULL);
	scanf("%lld", &t);
	for (ti = 1; ti <= t; ti++) {
		ans = 0;
		scanf("%lld", &n);
		setA();
		for (i = 0; i < n; i++) {
			scanf("%s", s);
			for (j = 0; j < n; j++)
				if (s[j] == '#')
					setB(i, j);
		}

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (b[i][j] > 0){
					setC(i, j);
					ans += b[i][j];
				}
		printf("Case #%lld\n%lld\n", ti, ans / 2);
	}
	return 0;
}