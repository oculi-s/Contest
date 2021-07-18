#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void _make0(int* M, bool* C, int i, int n) {
	C[i] = 0;
	if (i + M[i] < n)
		if (C[i + M[i]])
			C[i + M[i]] = 0, _make0(M, C, i + M[i], n);
	int j;
	for (j = 0; j < i; j++)
		if (C[j])
			if (M[j] == i - j)
				C[j] = 0, _make0(M, C, j, n);
}

int Answer;
int main(void)
{
	int T, test_case, n, i, * M;
	bool* C;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		scanf("%d", &n);
		M = malloc(sizeof(int) * n);
		C = malloc(sizeof(bool) * n);
		for (i = 0; i < n; i++)
			scanf("%d", M + i), C[i] = 1;
		Answer = 0;
		for (i = 0; i < n; i++)
			if (C[i])
				_make0(M, C, i, n), Answer++;
		printf("Case #%d\n", test_case + 1);
		printf("%d\n", Answer);
	}
	return 0;
}