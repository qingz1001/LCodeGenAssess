#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 800
#define MAX_K 15

long long dp[MAX_N][MAX_N][MAX_K + 1][MAX_K + 1];
int matrix[MAX_N][MAX_N];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0][matrix[0][0] % (k + 1)][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) continue;

            int val = matrix[i][j];
            for (int a = 0; a <= k; a++) {
                for (int b = 0; b <= k; b++) {
                    if (i > 0) {
                        int new_a = a;
                        int new_b = (b + val) % (k + 1);
                        dp[i][j][new_a][new_b] = (dp[i][j][new_a][new_b] + dp[i-1][j][a][b]) % MOD;
                    }
                    if (j > 0) {
                        int new_a = a;
                        int new_b = (b + val) % (k + 1);
                        dp[i][j][new_a][new_b] = (dp[i][j][new_a][new_b] + dp[i][j-1][a][b]) % MOD;
                    }
                }
            }
        }
    }

    long long result = 0;
    for (int a = 0; a <= k; a++) {
        result = (result + dp[n-1][m-1][a][a]) % MOD;
    }

    printf("%lld\n", result);

    return 0;
}