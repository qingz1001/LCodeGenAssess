#include <stdio.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int p[K];
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
    }

    int c[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    int dp[N];
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < p[i]; j++) {
            if (c[j] <= c[p[i] - 1]) {
                dp[j] = p[i];
            }
        }
    }

    int max_days = 0;
    for (int i = 0; i < N; i++) {
        max_days = (max_days > dp[i]) ? max_days : dp[i];
    }

    printf("%d\n", max_days);

    return 0;
}