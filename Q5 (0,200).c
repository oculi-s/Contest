#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Answer;
int main(void)
{
	int T, test_case;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		printf("Case #%d\n", test_case + 1);
		int N, K, a, b, c, t, i, j, eg = 0;
		scanf("%d %d", &N, &K);
		int** g = malloc(sizeof(int*) * 3);
		int** s = malloc(sizeof(int*) * 2);
		for (a = 0; a < 3; a++)
			g[a] = malloc(sizeof(int) * K * 2);
		for (a = 0; a < 2; a++)
			s[a] = malloc(sizeof(int) * K);

		int* V = malloc(sizeof(int) * (N + 1));
		bool** C = malloc(sizeof(bool*) * (N + 1));
		for (a = 1; a <= N; a++) {
			C[a] = malloc(sizeof(bool) * (N + 1));
			for (b = 1; b <= N; b++)
				C[a][b] = false;
		}

		int h, e, v, x, cnt;
		for (a = 0; a < K; a++) {
			scanf("%d %d %d", &t, &i, &j);
			if (t == 1) {
				scanf("%d", &b);
				if (C[i][j])
					for (c = 0; c < eg; c++)
						if (g[0][c] == i && g[1][c] == j)
							g[2][c] = b;
				else
					g[0][eg] = i, g[1][eg] = j, g[2][eg] = b, C[i][j] = 1, eg++;
				if (!C[j][i])
					g[0][eg] = j, g[1][eg] = i, g[2][eg] = -b, C[j][i] = 1, eg++;
			}
			else {
				for (b = 1; b <= N; b++)
					V[b] = 2;
				e = 0, s[0][0] = i, s[1][0] = 0, cnt = 0;
				while (e >= 0) {
					x = s[0][e], v = s[1][e], V[x]--, e--;
					if (x == j) {
						if (cnt > 0)
							if (h != v) {
								printf("CF\n");
								break;
							}
						cnt++, h = v;
					}
					for (c = 0; c < eg; c++)
						if (g[0][c] == x && V[g[1][c]])
							++e, s[0][e] = g[1][c], s[1][e] = v + g[2][c];
				}
				if (x != j)
					printf("NC\n");
				else if (h == v)
					printf("%d\n", v);
			}
		}
	}
	return 0;
}