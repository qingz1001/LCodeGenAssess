#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1005
#define MAXM 205

char A[MAXN], B[MAXM];
int n, m, k;
long long dp[MAXN][MAXM][2];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%s", A + 1);
    scanf("%s", B + 1);

    for (int i = 0; i <= n; i++) {
        dp[i][0][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int p = 0; p < 2; p++) {
                dp[i][j][p] = dp[i-1][j][p];
                if (A[i] == B[j]) {
                    if (j == 1 || p == 1) {
                        dp[i][j][1] = (dp[i][j][1] + dp[i-1][j-1][0] + dp[i-1][j-1][1]) % MOD;
                    }
                    if (j == 1) {
                        dp[i][j][1] = (dp[i][j][1] + 1) % MOD;
                    }
                }
            }
        }
    }

    long long result = 0;
    if (k == 1) {
        result = dp[n][m][1];
    } else {
        for (int i = k; i <= n; i++) {
            result = (result + dp[i][m][1] - dp[i-1][m][1] + MOD) % MOD;
        }
    }

    printf("%lld\n", result);

    return 0;
}