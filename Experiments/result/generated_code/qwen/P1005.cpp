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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][0] = max(matrix[i][0], matrix[i][m-1]) * (1 << 0);
    }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = max(dp[i][j-1] + matrix[i][j], dp[(i+1)%n][j-1] + matrix[i][j]);
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result += dp[i][m-1];
    }

    printf("%d\n", result);

    return 0;
}