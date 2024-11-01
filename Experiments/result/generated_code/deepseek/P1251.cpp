#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2001

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N;
    int r[MAXN];
    int p, m, f, n, s;
    int dp[MAXN][MAXN];

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &r[i]);
    }
    scanf("%d %d %d %d %d", &p, &m, &f, &n, &s);

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (dp[i-1][j] != INT_MAX) {
                // Buy new napkins
                dp[i][j + r[i]] = min(dp[i][j + r[i]], dp[i-1][j] + r[i] * p);

                // Use fast washing service
                if (i + m <= N) {
                    dp[i + m][j - r[i]] = min(dp[i + m][j - r[i]], dp[i-1][j] + r[i] * f);
                }

                // Use slow washing service
                if (i + n <= N) {
                    dp[i + n][j - r[i]] = min(dp[i + n][j - r[i]], dp[i-1][j] + r[i] * s);
                }
            }
        }
    }

    int min_cost = INT_MAX;
    for (int j = 0; j <= N; j++) {
        min_cost = min(min_cost, dp[N][j]);
    }

    printf("%d\n", min_cost);

    return 0;
}