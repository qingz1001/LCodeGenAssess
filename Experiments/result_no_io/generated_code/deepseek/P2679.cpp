#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1005
#define MAXM 205
#define MAXK 205

int dp[MAXN][MAXM][MAXK][2];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char A[MAXN], B[MAXM];
    scanf("%s", A + 1);
    scanf("%s", B + 1);

    dp[0][0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int p = 1; p <= k; p++) {
                if (A[i] == B[j]) {
                    dp[i][j][p][1] = (dp[i-1][j-1][p][1] + dp[i-1][j-1][p-1][0]) % MOD;
                }
                dp[i][j][p][0] = (dp[i-1][j][p][0] + dp[i][j][p][1]) % MOD;
            }
        }
    }

    int ans = (dp[n][m][k][0] + dp[n][m][k][1]) % MOD;
    printf("%d\n", ans);

    return 0;
}