#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int n;
int a[MAXN][3];
int dp[2][MAXN][3];

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
    }

    // Initialize dp array
    for (int j = 0; j < 3; j++) {
        dp[0][0][j] = a[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (k != j) {
                    dp[1][i][j] = max(dp[1][i][j], dp[0][i - 1][k] + a[i][j]);
                }
            }
        }
        for (int j = 0; j < 3; j++) {
            dp[0][i][j] = dp[1][i][j];
        }
    }

    int result = 0;
    for (int j = 0; j < 3; j++) {
        result = max(result, dp[0][n - 1][j]);
    }

    printf("%d\n", result);

    return 0;
}