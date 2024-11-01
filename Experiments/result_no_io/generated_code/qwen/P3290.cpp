#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, c, q;
    scanf("%d %d %d %d", &n, &m, &c, &q);

    int templates[q][c];
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < c; ++j) {
            char ch;
            scanf(" %c", &ch);
            if (ch == 'W') templates[i][j] = 1;
            else if (ch == 'B') templates[i][j] = 2;
            else templates[i][j] = 0;
        }
    }

    long long dp[n + 1][m + 1][3];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k < 3; ++k) {
                dp[i][j][k] = 0;
            }
        }
    }
    dp[0][0][0] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (dp[i][j][k] == 0) continue;
                if (i > 0) {
                    dp[i - 1][j][(k * 3 + 1) % 3] += dp[i][j][k];
                    dp[i - 1][j][(k * 3 + 2) % 3] += dp[i][j][k];
                    dp[i - 1][j][k] += dp[i][j][k];
                    dp[i - 1][j][k] %= MOD;
                }
                if (j > 0) {
                    dp[i][j - 1][(k * 3 + 1) % 3] += dp[i][j][k];
                    dp[i][j - 1][(k * 3 + 2) % 3] += dp[i][j][k];
                    dp[i][j - 1][k] += dp[i][j][k];
                    dp[i][j - 1][k] %= MOD;
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        long long count = 0;
        for (int j = 0; j <= n - 2; ++j) {
            for (int k = 0; k <= m - c; ++k) {
                int match = 1;
                for (int l = 0; l < c; ++l) {
                    if (templates[i][l] != 0 && templates[i][l] != dp[j][k + l][templates[i][l]]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    count += dp[j][k][0];
                    count %= MOD;
                }
            }
        }
        printf("%lld\n", count);
    }

    return 0;
}