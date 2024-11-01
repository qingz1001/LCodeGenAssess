#include <stdio.h>
#include <stdlib.h>

#define MAXN 6
#define MAXM 6

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solve(int matrix[MAXN][MAXM], int n, int m, int *result) {
    int dp[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[i][j];
            } else if (i == 0) {
                dp[i][j] = matrix[i][j] + max(dp[i][j - 1], 0);
            } else if (j == 0) {
                dp[i][j] = matrix[i][j] + max(dp[i - 1][j], 0);
            } else {
                dp[i][j] = matrix[i][j] + max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
            }
        }
    }
    *result = dp[n - 1][m - 1];
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int matrix[MAXN][MAXM];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        int result;
        solve(matrix, n, m, &result);
        printf("%d\n", result);
    }
    return 0;
}