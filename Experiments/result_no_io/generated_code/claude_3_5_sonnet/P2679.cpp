#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1005
#define MAXM 205

char A[MAXN], B[MAXM];
int dp[MAXN][MAXM][2];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    scanf("%s", A + 1);
    scanf("%s", B + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i] == B[j]) {
                dp[i][j][0] = (dp[i-1][j-1][0] + dp[i-1][j-1][1] + (j == 1 ? 1 : 0)) % MOD;
            }
            dp[i][j][1] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD;
        }
    }

    if (k == 1) {
        printf("%d\n", (dp[n][m][0] + dp[n][m][1]) % MOD);
    } else {
        long long ans = 0;
        for (int i = k; i <= n; i++) {
            ans = (ans + dp[i][m][0]) % MOD;
        }
        printf("%lld\n", ans);
    }

    return 0;
}