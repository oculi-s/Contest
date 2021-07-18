#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* Answer;
int main(void)
{
	int T, test_case;
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		int N, M, K, i, j, k, a, b;
		scanf("%d %d %d", &N, &M, &K);
		bool** G = malloc(sizeof(bool*) * (N+1));
		for (i = 0; i <= N; i++) {
			G[i] = malloc(sizeof(bool) * (N+1));
			for (j = 0; j <= N; j++)
				G[i][j] = false;
		}
		for (i = 0; i < M; i++) {
			scanf("%d %d", &a, &b);
			G[a][b] = 1;
		}
		int s[1000], e, v;
		k = 0;
		Answer = malloc(sizeof(char) * K);
		for (i = 0; i < K; i++) {
			scanf("%d %d", &a, &b);
			e = 0, s[0] = b;
			while (e >= 0) {
				v = s[e], e--;
				if (v == a) {
					Answer[k++] = '1';
					G[b][a] = 1;
					break;
				}
				for (j = 1; j <= N; j++)
					if (G[v][j])
						++e, s[e] = j;
			}
			if (v != a) {
				Answer[k++] = '0';
				G[a][b] = 1;
			}
		}
		Answer[k] = 0;
		printf("Case #%d\n", test_case + 1);
		printf("%s\n", Answer);
	}

	return 0;
}