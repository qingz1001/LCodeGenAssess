#include <stdio.h>
#include <string.h>

#define MAXN 300

int T, n, m, M;
int a[MAXN + 1], b[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &M);
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= m; i++) {
            int p, q;
            scanf("%d%d", &p, &q);
            a[q]++;
            b[p] = q;
        }

        dp[0][0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (dp[i][j]) {
                    for (int k = 1; k <= n; k++) {
                        if (a[k] == 0) {
                            int x = k, y = j + 1;
                            while (x <= n && b[x] == 0) {
                                if (x == k) y++;
                                x++;
                            }
                            if (x > n) dp[n][y] = (dp[n][y] + dp[i][j]) % M;
                            else dp[x - 1][y] = (dp[x - 1][y] + dp[i][j]) % M;
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + dp[i][n - i]) % M;
        }
        if (ans) printf("YES %d\n", ans);
        else printf("NO\n");
    }
    return 0;
}