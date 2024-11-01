#include <stdio.h>
#include <string.h>

#define MOD 9901

int dp[201][101];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(dp, 0, sizeof(dp));
    dp[1][1] = 1;

    for (int i = 3; i <= n; i += 2) {
        for (int j = 1; j <= k; j++) {
            for (int left = 1; left < i; left += 2) {
                int right = i - 1 - left;
                if (right > 0) {
                    for (int left_depth = 1; left_depth < j; left_depth++) {
                        dp[i][j] = (dp[i][j] + dp[left][left_depth] * dp[right][j - 1]) % MOD;
                        dp[i][j] = (dp[i][j] + dp[left][j - 1] * dp[right][left_depth]) % MOD;
                    }
                    dp[i][j] = (dp[i][j] + dp[left][j - 1] * dp[right][j - 1]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int j = 1; j <= k; j++) {
        result = (result + dp[n][j]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}