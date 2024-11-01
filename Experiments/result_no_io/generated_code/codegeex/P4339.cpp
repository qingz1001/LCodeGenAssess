#include <stdio.h>
#include <string.h>

#define maxn 100
#define maxm 1000000

int m, k, dp[maxn][maxm];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &m, &k);
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int maxn = 0;
        for (int i = 0; i < maxm; i++) {
            for (int j = 0; j < m; j++) {
                if (dp[(i + j) % k][j]) {
                    dp[(i + j) % k][j] += dp[i][j];
                    maxn = maxn > (i + j) % k ? maxn : (i + j) % k;
                }
            }
        }
        int ans = -1;
        for (int i = 0; i < k; i++) {
            if (maxn == i) {
                for (int j = 0; j < m; j++) {
                    if (dp[i][j] > 1) {
                        ans = 1;
                        break;
                    }
                }
            }
        }
        if (ans == -1) {
            printf("%d\n", maxn + 1);
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}