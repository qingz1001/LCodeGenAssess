#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 6
#define MAX_STATE (1 << MAX_M)

int n, m;
int a[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][MAX_STATE];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(dp, -0x3f, sizeof(dp));
    int result = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j][1 << j] = a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 1; s < (1 << m); s++) {
                if (!(s & (1 << j))) continue;
                
                if (j > 0 && (s & (1 << (j-1)))) {
                    dp[i][j][s] = max(dp[i][j][s], dp[i][j-1][s ^ (1 << j)] + a[i][j]);
                }
                if (j < m-1 && (s & (1 << (j+1)))) {
                    dp[i][j][s] = max(dp[i][j][s], dp[i][j+1][s ^ (1 << j)] + a[i][j]);
                }
                if (i > 0) {
                    dp[i][j][s] = max(dp[i][j][s], dp[i-1][j][s ^ (1 << j)] + a[i][j]);
                }
                if (i < n-1) {
                    dp[i][j][s] = max(dp[i][j][s], dp[i+1][j][s ^ (1 << j)] + a[i][j]);
                }

                if (__builtin_popcount(s) >= 4) {
                    result = max(result, dp[i][j][s]);
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}