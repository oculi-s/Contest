#include <stdio.h>
#include <stdlib.h>

char a[1050], b[1050];

int main(void)
{
	int T, test_case, n, t, i;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		scanf("%d %d", &n, &t);
		scanf("%s", b);
		for (i = 0; i < n; i++)
			a[i] = '2';
		for (i = 0; i < t; i++)
			a[i + t] = b[i] == '1' ? '1' : '0';
		for (i = n - t; i < n; i++)
			a[i - t] = b[i] == '1' ? '1' : '0';
		for (i = 0; i < n; i++) {
			if (b[i] == '0') {
				if (i - t >= 0)
					a[i - t] = '0';
				if (i + t < n)
					a[i + t] = '0';
			}
		}
		for (i = 0; i < n; i++)
			if (b[i] == '1') {
				if (i - t >= 0)
					if (a[i + t] == '2' && a[i - t] != '2')
						a[i + t] = a[i - t] == '1' ? '0' : '1';
				if (i + t < n)
					if (a[i - t] == '2' && a[i + t] != '2')
						a[i - t] = a[i + t] == '1' ? '0' : '1';
			}
		for (int j = 0; j < t; j++) {
			for (i = n - t; i > t; i--) {
				if (a[i] == '2' && b[i + t] == '1' && b[i - t] == '1') {
					a[i] = '1';
					if (i - 2 * t >= 0)
						a[i - 2 * t] = '0';
					if (i + 2 * t < n)
						a[i + 2 * t] = '0';
				}
			}
		}
		for (i = 0; i < n; i++)
			a[i] = a[i] == '1' ? '1' : '0';
		a[i] = 0;
		printf("Case #%d\n", test_case + 1);
		printf("%s\n", a);
	}
	return 0;
}