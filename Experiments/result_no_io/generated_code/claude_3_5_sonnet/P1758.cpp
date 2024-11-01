#include <stdio.h>
#include <string.h>

#define MOD 1024523
#define MAX_N 501

int dp[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];
char up[MAX_N], down[MAX_N];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", up);
    scanf("%s", down);

    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i > 0 && j > 0 && up[i-1] == down[j-1]) {
                dp[i][j] = (dp[i][j] + sum[i-1][j-1]) % MOD;
            }
            if (i > 0) {
                sum[i][j] = (sum[i-1][j] + dp[i][j]) % MOD;
            }
            if (j > 0) {
                sum[i][j] = (sum[i][j] + dp[i][j]) % MOD;
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            result = (result + (long long)dp[i][j] * dp[i][j]) % MOD;
        }
    }

    printf("%d\n", result);
    return 0;
}