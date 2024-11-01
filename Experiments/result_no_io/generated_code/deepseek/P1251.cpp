#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2001

int N;
int r[MAXN];
int p, m, f, n, s;
int dp[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
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
                // 购买新餐巾
                dp[i][j + r[i]] = min(dp[i][j + r[i]], dp[i-1][j] + r[i] * p);

                // 快洗部
                if (i + m <= N) {
                    dp[i + m][j + r[i] - r[i + m]] = min(dp[i + m][j + r[i] - r[i + m]], dp[i-1][j] + r[i] * f);
                }

                // 慢洗部
                if (i + n <= N) {
                    dp[i + n][j + r[i] - r[i + n]] = min(dp[i + n][j + r[i] - r[i + n]], dp[i-1][j] + r[i] * s);
                }
            }
        }
    }

    int result = INT_MAX;
    for (int j = 0; j <= N; j++) {
        result = min(result, dp[N][j]);
    }

    printf("%d\n", result);

    return 0;
}