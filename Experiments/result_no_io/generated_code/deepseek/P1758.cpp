#include <stdio.h>
#include <string.h>

#define MOD 1024523
#define MAXN 505

int dp[MAXN][MAXN][MAXN];
char upper[MAXN], lower[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", upper + 1);
    scanf("%s", lower + 1);

    dp[0][0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n; k++) {
                int l = i + j - k;
                if (l < 0 || l > m) continue;

                if (i < n && k < n && upper[i + 1] == upper[k + 1]) {
                    dp[i + 1][j][k + 1] = (dp[i + 1][j][k + 1] + dp[i][j][k]) % MOD;
                }
                if (i < n && l < m && upper[i + 1] == lower[l + 1]) {
                    dp[i + 1][j][k] = (dp[i + 1][j][k] + dp[i][j][k]) % MOD;
                }
                if (j < m && k < n && lower[j + 1] == upper[k + 1]) {
                    dp[i][j + 1][k + 1] = (dp[i][j + 1][k + 1] + dp[i][j][k]) % MOD;
                }
                if (j < m && l < m && lower[j + 1] == lower[l + 1]) {
                    dp[i][j + 1][k] = (dp[i][j + 1][k] + dp[i][j][k]) % MOD;
                }
            }
        }
    }

    printf("%d\n", dp[n][m][n]);
    return 0;
}