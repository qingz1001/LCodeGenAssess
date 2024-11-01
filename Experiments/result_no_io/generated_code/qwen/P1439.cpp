#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int P1[MAXN], P2[MAXN];
int dp[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &P1[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &P2[i]);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (P1[i - 1] == P2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    printf("%d\n", dp[n][n]);

    return 0;
}