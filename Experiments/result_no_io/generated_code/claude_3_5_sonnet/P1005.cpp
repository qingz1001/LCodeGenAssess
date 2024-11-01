#include <stdio.h>
#include <string.h>

#define MAX_N 80
#define MAX_M 80

long long dp[MAX_N][MAX_M][MAX_M];
int matrix[MAX_N][MAX_M];
int n, m;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j][j] = matrix[i][j] << (m - 1);
        }
    }

    for (int len = 2; len <= m; len++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m - len; j++) {
                int k = j + len - 1;
                dp[i][j][k] = max(matrix[i][j] * (1LL << (m - len)) + dp[i][j+1][k],
                                  matrix[i][k] * (1LL << (m - len)) + dp[i][j][k-1]);
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += dp[i][0][m-1];
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("%lld\n", solve());
    return 0;
}