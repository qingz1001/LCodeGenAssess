#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char A[n + 1], B[m + 1];
    scanf("%s %s", A, B);

    if (m * k > n) {
        printf("0\n");
        return 0;
    }

    int dp[k + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - m * i; j++) {
            for (int l = 0; l <= n - j; l++) {
                if (strncmp(A + j + l, B, m) == 0) {
                    dp[i][j + l + m] = (dp[i][j + l + m] + dp[i - 1][j]) % MOD;
                }
            }
        }
    }

    printf("%d\n", dp[k][n]);
    return 0;
}