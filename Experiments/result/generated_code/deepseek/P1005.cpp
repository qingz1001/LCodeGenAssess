#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 80
#define MAXM 80

int n, m;
int matrix[MAXN][MAXM];
long long dp[MAXM][MAXM];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long solve_row(int row) {
    memset(dp, 0, sizeof(dp));
    for (int len = 1; len <= m; ++len) {
        for (int i = 0; i + len - 1 < m; ++i) {
            int j = i + len - 1;
            long long power = 1LL << (m - len + 1);
            if (i == j) {
                dp[i][j] = matrix[row][i] * power;
            } else {
                dp[i][j] = max(dp[i+1][j] + matrix[row][i] * power, dp[i][j-1] + matrix[row][j] * power);
            }
        }
    }
    return dp[0][m-1];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    long long total_score = 0;
    for (int i = 0; i < n; ++i) {
        total_score += solve_row(i);
    }

    printf("%lld\n", total_score);
    return 0;
}