#include <stdio.h>
#include <stdint.h>

#define MOD 998244353
#define MAXN 64
#define MAXM 20000

int n, m;
int64_t A[MAXN][MAXN];
int64_t dp[MAXM + 1][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &A[i][j]);
        }
    }

    int64_t result = 0;

    for (int x = 1; x <= m; x++) {
        for (int y = 0; y < n; y++) {
            if (x == 1) {
                dp[x][y] = 0;
                for (int i = 0; i < n; i++) {
                    dp[x][y] = (dp[x][y] + A[i][y]) % MOD;
                }
            } else {
                dp[x][y] = 0;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if ((i & j) == y) {
                            dp[x][y] = (dp[x][y] + dp[x - 1][i] * A[j][y]) % MOD;
                        }
                    }
                }
            }
            result ^= dp[x][y];
        }
    }

    printf("%lld\n", result);
    return 0;
}