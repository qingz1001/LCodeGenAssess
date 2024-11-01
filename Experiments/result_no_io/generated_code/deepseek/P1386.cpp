#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 305
#define MOD 1000000007

int n, m, M;
int fixed[MAXN];
int dp[MAXN][MAXN];

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (fixed[i] == 0) {
                dp[i][j] = (dp[i][j] + (long long)dp[i-1][j] * j % M) % M;
                if (j > 0) {
                    dp[i][j] = (dp[i][j] + (long long)dp[i-1][j-1] * (n - j + 1) % M) % M;
                }
            } else {
                if (j > 0) {
                    dp[i][j] = (dp[i][j] + (long long)dp[i-1][j-1] % M) % M;
                }
            }
        }
    }

    return dp[n][n];
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d %d", &n, &m, &M);
        memset(fixed, 0, sizeof(fixed));

        for (int i = 0; i < m; i++) {
            int p, q;
            scanf("%d %d", &p, &q);
            fixed[p] = q;
        }

        int result = solve();
        if (result > 0) {
            printf("YES %d\n", result);
        } else {
            printf("NO\n");
        }
    }

    return 0;
}