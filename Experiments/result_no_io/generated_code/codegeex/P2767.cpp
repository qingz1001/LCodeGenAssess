#include <stdio.h>

#define MOD 10007

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    if (n == 0) {
        printf("1\n");
        return 0;
    }

    long long dp[128][128] = {0};
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k < j; k++) {
                dp[i][j] = (dp[i][j] + dp[i-j][k] * dp[j-1][m-1]) % MOD;
            }
        }
    }

    long long result = 0;
    for (int j = 1; j <= n; j++) {
        result = (result + dp[n][j]) % MOD;
    }

    printf("%lld\n", result);
    return 0;
}