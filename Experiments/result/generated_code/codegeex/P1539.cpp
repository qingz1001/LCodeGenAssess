#include <stdio.h>
#include <string.h>

#define MOD 10007

int n, m;
int mat[230][230];
int dp[230][230][2];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            scanf(" %c", &ch);
            mat[i][j] = ch - '0';
        }
    }

    dp[1][1][mat[1][1]] = 1;
    dp[1][1][mat[1][1]^1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1) {
                dp[i][j][0] = (dp[i-1][j][1] + dp[i][j][0]) % MOD;
                dp[i][j][1] = (dp[i-1][j][0] + dp[i][j][1]) % MOD;
            }
            if (j > 1) {
                dp[i][j][0] = (dp[i][j-1][1] + dp[i][j][0]) % MOD;
                dp[i][j][1] = (dp[i][j-1][0] + dp[i][j][1]) % MOD;
            }
        }
    }

    int result = (dp[n][m][0] + dp[n][m][1]) % MOD;
    printf("%d\n", result);

    return 0;
}