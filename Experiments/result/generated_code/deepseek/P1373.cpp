#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 800
#define MAXK 15

int n, m, k;
int matrix[MAXN][MAXN];
int dp[MAXN][MAXN][MAXK][2];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0][matrix[0][0]][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x <= k; x++) {
                if (i + 1 < n) {
                    int new_x = (x + matrix[i + 1][j]) % (k + 1);
                    dp[i + 1][j][new_x][1] = (dp[i + 1][j][new_x][1] + dp[i][j][x][0]) % MOD;
                }
                if (j + 1 < m) {
                    int new_x = (x + matrix[i][j + 1]) % (k + 1);
                    dp[i][j + 1][new_x][1] = (dp[i][j + 1][new_x][1] + dp[i][j][x][0]) % MOD;
                }
                if (i + 1 < n) {
                    int new_x = (x + matrix[i + 1][j]) % (k + 1);
                    dp[i + 1][j][new_x][0] = (dp[i + 1][j][new_x][0] + dp[i][j][x][1]) % MOD;
                }
                if (j + 1 < m) {
                    int new_x = (x + matrix[i][j + 1]) % (k + 1);
                    dp[i][j + 1][new_x][0] = (dp[i][j + 1][new_x][0] + dp[i][j][x][1]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result = (result + dp[i][j][0][1]) % MOD;
        }
    }

    printf("%d\n", result);
    return 0;
}