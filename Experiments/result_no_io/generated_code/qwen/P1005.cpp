#include <stdio.h>
#include <stdlib.h>

#define MAXN 85
#define MAXM 85

int dp[MAXN][MAXM];
int matrix[MAXN][MAXM];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i][1] = max(matrix[i][1], matrix[i][m]);
    }

    for (int j = 2; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = max(dp[i-1][j-1] + matrix[i][j], dp[i][j-1]);
        }
    }

    printf("%d\n", dp[n][m]);

    return 0;
}