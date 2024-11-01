#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

double dp[MAX_N];

int cmp(const void *a, const void *b) {
    if (*(double*)a > *(double*)b) return -1;
    if (*(double*)a < *(double*)b) return 1;
    return 0;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        dp[i] = 1.0 / i;
    }

    for (int round = 1; round < k; round++) {
        qsort(dp + 1, n, sizeof(double), cmp);
        
        for (int i = 2; i <= n; i++) {
            dp[i] += dp[i-1];
        }
    }

    qsort(dp + 1, n, sizeof(double), cmp);

    printf("%.9f\n", dp[1]);

    return 0;
}