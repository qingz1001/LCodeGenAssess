#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int *p = (int *)malloc(K * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    // Sort the days that must be used
    qsort(p, K, sizeof(int), compare);

    // Check if the sequence is strictly increasing
    for (int i = 1; i < K; i++) {
        if (c[p[i] - 1] <= c[p[i - 1] - 1]) {
            printf("impossible\n");
            free(p);
            free(c);
            return 0;
        }
    }

    // Find the longest increasing subsequence
    int *dp = (int *)malloc(N * sizeof(int));
    memset(dp, 0, N * sizeof(int));
    int len = 0;

    for (int i = 0; i < N; i++) {
        int idx = (int)(lower_bound(dp, dp + len, c[i]) - dp);
        dp[idx] = c[i];
        if (idx == len) {
            len++;
        }
    }

    free(dp);

    // Calculate the maximum number of days
    int max_days = len + (N - K);
    printf("%d\n", max_days);

    free(p);
    free(c);
    return 0;
}