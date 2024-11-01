#include <stdio.h>
#include <string.h>

#define MOD 1024523
#define MAXN 501

int n, m;
char up[MAXN], down[MAXN];
int dp[MAXN][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", up);
    scanf("%s", down);

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i > 0 && j > 0 && up[i-1] == down[j-1]) {
                dp[i][j] = (dp[i][j] + (long long)dp[i-1][j] * dp[i][j-1]) % MOD;
            }
            if (i < n) {
                dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;
            }
            if (j < m) {
                dp[i][j+1] = (dp[i][j+1] + dp[i][j]) % MOD;
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= n; i++) {
        result = (result + (long long)dp[i][m] * dp[i][m]) % MOD;
    }

    printf("%d\n", result);

    return 0;
}