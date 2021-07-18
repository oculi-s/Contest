#include <stdio.h>
#define X 20000000

void _sort4_min(long long a[4], long long t) {
	if (t < a[0])
		a[3] = a[2], a[2] = a[1], a[1] = a[0], a[0] = t;
	else if (t < a[1])
		a[3] = a[2], a[2] = a[1], a[1] = t;
	else if (t < a[2])
		a[3] = a[2], a[2] = t;
	else if (t < a[3])
		a[3] = t;
}

void _sort2_max(long long a[2], long long t) {
	if (t > a[0])
		a[1] = a[0], a[0] = t;
	else if (t > a[1])
		a[1] = t;
}

long long Answer;
int main(void)
{
	int T, test_case, cnt = 0;
	long long N, M, i, j, l, t, a[4], b[2], TA = X;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		b[0] = 0, b[1] = 0;
		Answer = 0;
		scanf("%lld %lld", &N, &M);
		for (i = 0; i < N; i++) {
			a[0] = X, a[1] = X, a[2] = X, a[3] = X;
			scanf("%lld", &l);
			for (j = 0; j < l; j++) {
				scanf("%lld", &t);
				_sort4_min(a, t);
			}
			_sort2_max(b, a[2] + a[3]);
			Answer += (a[0] + a[1] + a[2] + a[3]);
			if (l % 2 == 1)
				Answer += a[0], cnt++;
			else
				TA = a[0] < TA ? a[0] : TA;
		}
		if (cnt % 2)
			Answer += TA;
		Answer -= (b[0] + b[1]);
		printf("Case #%d\n", test_case + 1);
		printf("%lld\n", Answer);
	}
	return 0;
}