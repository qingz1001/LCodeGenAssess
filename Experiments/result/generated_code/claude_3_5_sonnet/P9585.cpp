#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int n, m;
int dp[101][101][2];

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0][0] = 0;
    dp[1][1][1] = 0;

    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= MIN(i, n); j++) {
            if (j < i) {
                dp[i][j][0] = MIN(dp[i-1][j][0], dp[i-1][j][1]);
            }
            if (j > 0) {
                dp[i][j][1] = MIN(dp[i-1][j-1][0], dp[i-1][j-1][1] + 1);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int j = 0; j <= 1; j++) {
        ans = MIN(ans, dp[m][n][j] + j);
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    printf("%d\n", solve());
    return 0;
}