#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXT 10

int T, n, K, L;
long long a[MAXN], b[MAXN];
long long ans[MAXT];

void solve() {
    int i, j, k;
    long long sum_a, sum_b, max_sum;
    int count;

    for (i = 0; i < n; i++) {
        a[i] += b[i];
    }

    qsort(a, n, sizeof(long long), compare);

    max_sum = -1;
    for (i = 0; i <= K; i++) {
        sum_a = 0;
        sum_b = 0;
        count = 0;
        for (j = 0; j < i; j++) {
            sum_a += a[j];
        }
        for (k = n - 1; k >= n - K + i; k--) {
            sum_b += a[k];
        }
        if (i >= L) {
            max_sum = (max_sum > sum_a + sum_b ? max_sum : sum_a + sum_b);
        }
    }

    ans[T] = max_sum;
}

int main() {
    int i, j;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &K, &L);
        for (i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        for (i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
        }
        solve();
    }
    for (i = 0; i < T; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}