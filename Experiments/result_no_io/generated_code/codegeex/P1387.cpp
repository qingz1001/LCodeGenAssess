#include <stdio.h>

#define MAXN 101

int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];

int min(int a, int b, int c) {
    int t = a < b ? a : b;
    return t < c ? t : c;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int maxLen = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (matrix[i][j] == 1) {
                dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                }
            }
        }
    }

    printf("%d\n", maxLen);
    return 0;
}