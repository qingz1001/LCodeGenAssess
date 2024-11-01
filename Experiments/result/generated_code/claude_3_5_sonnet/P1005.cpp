#include <stdio.h>
#include <string.h>

#define MAX_N 80
#define MAX_M 80

long long dp[MAX_N][MAX_M][MAX_M];
int matrix[MAX_N][MAX_M];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));

    for (int i = n - 1; i >= 0; i--) {
        for (int left = 0; left < m; left++) {
            for (int right = 0; right < m; right++) {
                int remaining = m - (left + (m - 1 - right));
                if (remaining < 0) continue;

                long long score = 0;
                if (remaining == 0) {
                    score = 0;
                } else if (left == m - 1 - right) {
                    score = (long long)matrix[i][left] << (m - remaining);
                } else {
                    long long take_left = matrix[i][left] + dp[i + 1][left + 1][right];
                    long long take_right = matrix[i][right] + dp[i + 1][left][right - 1];
                    score = max(take_left, take_right) << 1;
                }

                dp[i][left][right] = score;
            }
        }
    }

    printf("%lld\n", dp[0][0][m - 1]);

    return 0;
}