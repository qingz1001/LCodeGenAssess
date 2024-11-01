#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int dp[1001][101][101];

int main() {
    int n, m, k;
    char A[1001], B[101];
    scanf("%d %d %d", &n, &m, &k);
    scanf("%s %s", A, B);

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; i++) {
        dp[i][0][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m && j <= k; j++) {
            for (int l = 0; l <= k; l++) {
                dp[i][j][l] = dp[i - 1][j][l];
                if (j > 0) {
                    dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j - 1][l]) % MOD;
                }
                if (l > 0 && strlen(A + i - 1) >= strlen(B + j - 1)) {
                    int match = 1;
                    for (int p = 0; p < strlen(B + j - 1); p++) {
                        if (A[i - 1 + p] != B[j - 1 + p]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        dp[i][j][l] = (dp[i][j][l] + dp[i - strlen(B + j - 1)][j][l - 1]) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", dp[n][m][k]);
    return 0;
}