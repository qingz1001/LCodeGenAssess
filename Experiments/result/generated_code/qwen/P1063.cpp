#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

int dp[MAXN][MAXN];
int a[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = 0;
            for (int k = i; k < j; k++) {
                dp[i][j] = fmax(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i] * a[k] * a[j]);
            }
        }
    }
    printf("%d\n", dp[0][n - 1]);
    return 0;
}