#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    qsort(lengths, n, sizeof(int), compare);

    long long dp[m + 1][n];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1]) % MOD;
        }
    }

    int max_length = 0;
    for (int i = 1; i < n; i++) {
        if (max_length == 0 || (lengths[i] - lengths[0] < lengths[max_length] - lengths[max_length - 1])) {
            max_length = i;
        }
    }

    printf("%d %lld\n", lengths[max_length], dp[m][max_length]);

    return 0;
}